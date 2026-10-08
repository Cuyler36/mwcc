#define CERROR_FILE "CLLicenses.c"
#include "compiler/common.h"
#include "driver/CLLicenses.h"
#include "driver/CLErrors.h"
#include "driver/CLTarg.h"
#include "driver/LicenseImports.h"
/* GC3 uses the newer Windows allocation and path-construction ABI. */
extern void *__stdcall xcalloc(const char *context, unsigned int size);
extern void __stdcall xfree(void *memory);
extern DWORD __stdcall OS_MakeSpec(const char *path, int mode, void *unused, OSSpec *spec);
extern unsigned char CLLicenses_HasAlternatePath;
extern char CLLicenses_AlternatePath[];
struct CLLicenses_PathSpec {
    char directory[260];
    char name[256];
};

UInt32 license_slots[32][2] = {{0}};
int license_id_counter = 0;
int license_slot_count = 0;
struct License *data_0057ef08 = NULL;
#include "driver/MsDos.h"
/* Paired values in the license table. */

#include <string.h>
int get_license_slot_values(int index, unsigned int *firstValue, int *secondValue)
{
    if (((0 <= index) && (index < license_slot_count)) && (license_slots[index][1] != 0)) {
        *firstValue = license_slots[index][0];
        *secondValue = license_slots[index][1];
        return 1;
    }
    return 0;
}
int delete_license(int licenseIndex)
{
    if (licenseIndex >= 0 && licenseIndex < license_slot_count) {
        license_slots[licenseIndex][1] = 0;
        license_slots[licenseIndex][0] = 0;
        if (licenseIndex + 1 == license_slot_count) {
            for (; licenseIndex >= 0 && license_slots[licenseIndex][1] == 0; --licenseIndex) {
                --license_slot_count;
            }
        }
        return 1;
    }
    CLErrors_ReportInternalError("CLLicenses.c", 0xa3, "Deleted license not valid");
    return 0;
}

int get_license_slot_count(void)
{
    return license_slot_count;
}

void fn_00417750(void)
{
    license_slot_count = 0;
    data_0057ef08 = NULL;
    return;
}

void CLLicenses_ReleaseLicenses(void)
{
    int index;
    unsigned int firstValue;
    int count;
    release_negative_license_values();
    for (index = 0; index < (int)((long (*)(void))get_license_slot_count)(); index++) {
        if (((long (*)(int, unsigned int *, int *))get_license_slot_values)(index, &firstValue, &count) != 0 &&
            count > 0) {
            CLLicenses_DeleteLicense(count);
        }
    }
    if (data_0057ef08 != NULL) {
        memset(data_0057ef08, 0, 0x27c);
        xfree(data_0057ef08);
        data_0057ef08 = NULL;
    }
}

int CLLicenses_RequestLicense(int request, int options, int cookieKind, char *errorMessage)
{
    char licensePath[260];
    MWInfo licenseInfo;
    struct CLLicenses_PathSpec alternatePath;
    int licenseHandle = 0;
    int result = 0;
    int status;
    Boolean found = 0;

    licensePath[0] = 0;
    if (license_path != NULL) {
        strncpy(licensePath, license_path, sizeof(licensePath) - 1);
        found = 1;
    }
    if (!found) {
        fn_00412340(data_005871d8.directory.path, licensePath, sizeof(data_005871d8.directory.path));
        strcat(licensePath, "license.dat");
        if (OS_MakeSpec(licensePath, 1, NULL, (OSSpec *)&alternatePath) == 0 && OS_Status((OSSpec *)&alternatePath) == 0)
            found = 1;
    }
    if (!found) {
        strcpy(licensePath, "license.dat");
        if (OS_MakeSpec(licensePath, 1, NULL, (OSSpec *)&alternatePath) == 0 && OS_Status((OSSpec *)&alternatePath) == 0)
            found = 1;
    }
    if (!found && CLLicenses_HasAlternatePath) {
        fn_00412340(CLLicenses_AlternatePath, licensePath, sizeof(data_005871d8.directory.path));
        strcat(licensePath, "..\\license.dat");
        if (OS_MakeSpec(licensePath, 1, NULL, (OSSpec *)&alternatePath) == 0 && OS_Status((OSSpec *)&alternatePath) == 0)
            found = 1;
    }
    if (data_0057ef08 == NULL) {
        data_0057ef08 = xcalloc(NULL, 0x27c);
        data_0057ef08->type = 4;
        data_0057ef08->k4 = 0x9b706081;
        data_0057ef08->k8 = 0x01c8e6a0;
        data_0057ef08->k10 = 0xa8e04e6e;
        data_0057ef08->kc = 0x4305b9b2;
        data_0057ef08->k18 = 0xdad4fa7a;
        data_0057ef08->k14 = 0xe1f34d09;
        data_0057ef08->w1c = 8;
        data_0057ef08->w1e = 4;
        data_0057ef08->b20 = 0;
        data_0057ef08->b21 = 0;
        strncpy(data_0057ef08->blob, "08.0", sizeof("08.0"));
    }
    licenseInfo.license = data_0057ef08;
    licenseInfo.vendor = "metrowks";
    status = fn_004270ba(&licenseInfo, 0x101, request, options, 1, found ? licensePath : NULL, &licenseHandle);
    strcpy(errorMessage, "No failure");
    if (status == 0) {
        result = allocate_license_slot(licenseHandle, cookieKind);
        if (result == 0) {
            strcpy(errorMessage, "Memory error:  Could not store license cookie");
            fn_004270c0(licenseHandle);
        }
    } else {
        strcpy(errorMessage, fn_004270c6(licenseHandle));
        fn_004270c0(licenseHandle);
    }
    return result;
}

void CLLicenses_DeleteLicense(int identifier)
{
    int licenseIndex;
    unsigned int license;

    if (0 < identifier) {
        licenseIndex = find_license(identifier, &license);
        if (licenseIndex >= 0) {
            int (*removeLicense)(int) = delete_license;
            removeLicense(licenseIndex);
            fn_004270c0(license);
        }
    }
}

/* A license value paired with its lookup identifier. */

int find_license(unsigned int identifier, unsigned int *license)
{
    int index;

    for (index = 0; index < license_slot_count; ++index) {
        int storedIdentifier = license_slots[index][1];
        if (identifier == storedIdentifier || identifier == -storedIdentifier) {
            *license = license_slots[index][0];
            return index;
        }
    }
    CLErrors_ReportInternalError("CLLicenses.c", 0x7e, "Searched license not found");
    return -1;
}

/* An opaque license value paired with its signed identifier. */

int allocate_license_slot(int licenseData, int negateId)
{
    int slot;

    slot = 0;
    if (0 < license_slot_count) {
        do {
            if (license_slots[slot][1] == 0)
                break;
            slot = slot + 1;
        } while (slot < license_slot_count);
    }
    if (slot >= 0x20) {
        release_negative_license_values();
        slot = license_slot_count;
    }
    if (slot < 0x20) {
        license_id_counter = license_id_counter + 1;
        license_slots[slot][0] = licenseData;
        license_slots[slot][1] = (negateId != 0) ? -license_id_counter : license_id_counter;
        if (slot >= license_slot_count) {
            license_slot_count = license_slot_count + 1;
        }
        return license_id_counter;
    }
    CLErrors_ReportInternalError("CLLicenses.c", 0x6a, "Out of license space");
    return 0;
}

static inline int license_count(void)
{
    int (*count)(void) = get_license_slot_count;
    return count();
}

int release_negative_license_values(void)
{
    int index;
    unsigned int firstValue;
    int secondValue;

    for (index = 0; index < license_count(); index++) {
        int (*lookup)(int, unsigned int *, int *) = get_license_slot_values;
        if (lookup(index, &firstValue, &secondValue) && secondValue < 0) {
            void (*release)(int) = CLLicenses_DeleteLicense;
            release(secondValue);
        }
    }
}
