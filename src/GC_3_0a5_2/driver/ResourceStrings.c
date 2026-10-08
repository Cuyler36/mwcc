#include "compiler/common.h"
#include <stdio.h>

/* Original ResourceStrings.c names and layout from the GC 3.0 symbol map. */
static struct {
    char *name;
    short rsrcid;
    char **strings;
} rlist[16];

int Res_AddResource(char *resourceData, short resourceId, char **resourceValue)
{
    int i;

    for (i = 0; i < 16 && rlist[i].rsrcid != 0; ++i) {
        if (resourceId == rlist[i].rsrcid) {
            fprintf(stderr, "Resource %d is already added!\n", resourceId);
            return 0;
        }
    }
    if (i >= 16) {
        return 0;
    }
    rlist[i].name = resourceData;
    rlist[i].rsrcid = resourceId;
    rlist[i].strings = resourceValue;
    return 1;
}

char *Res_GetResource(short id, short index)
{
    int i;
    int j;
    static char err[256];
    index--;
    for (i = 0; i < 16; i++) {
        if (id == rlist[i].rsrcid) {
            j = 0;
            if (index < 0) {
                snprintf(err, sizeof(err), "[Illegal string index #%d in list '%s' (%d)]", index,
                        rlist[i].name, id);
                return err;
            }
            while (j <= index) {
                if (rlist[i].strings[j] == NULL) {
                    snprintf(err, sizeof(err), "[String #%d not found in resource '%s' (%d)]", index + 1,
                            rlist[i].name, id);
                    return err;
                }
                if (j == index)
                    return rlist[i].strings[j];
                j++;
            }
        }
    }
    return NULL;
}
