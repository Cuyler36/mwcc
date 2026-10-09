#include "compiler/common.h"
#include <stddef.h>

/* Recovered machine601 descriptor, sparse opcode metadata and native pipeline. */
typedef struct Machine601Info {
    UInt8 unit;
    SInt8 latency;
    SInt8 cycles[4];
} Machine601Info;
typedef struct Machine601Opcode {
    SInt16 opcode;
    Machine601Info info;
} Machine601Opcode;
typedef struct Machine601Instruction {
    UInt8 unknown00[16];
    UInt32 flags;
    UInt8 unknown14[20];
    SInt16 opcode;
    SInt16 operandCount;
} Machine601Instruction;
typedef struct Machine601Stage {
    Machine601Instruction *instruction;
    UInt32 count;
} Machine601Stage;
typedef char Machine601InfoSize[sizeof(Machine601Info) == 6 ? 1 : -1];
typedef char Machine601OpcodeSize[sizeof(Machine601Opcode) == 8 ? 1 : -1];
typedef char Machine601OpcodeOffset[offsetof(Machine601Instruction, opcode) == 40 ? 1 : -1];
typedef char Machine601StageSize[sizeof(Machine601Stage) == 8 ? 1 : -1];

static Machine601Opcode nativeOpcodeTable[264] = {
    {496, {7, 1, {1, 0, 0, 0}}},
    {0, {5, 0, {0, 0, 0, 1}}},
    {1, {5, 0, {0, 0, 0, 1}}},
    {2, {5, 0, {0, 0, 0, 1}}},
    {3, {5, 0, {0, 0, 0, 1}}},
    {4, {5, 0, {0, 0, 0, 1}}},
    {5, {5, 0, {0, 0, 0, 1}}},
    {6, {5, 0, {0, 0, 0, 1}}},
    {7, {5, 0, {0, 0, 0, 1}}},
    {8, {5, 0, {0, 0, 0, 1}}},
    {9, {5, 0, {0, 0, 0, 1}}},
    {10, {5, 0, {0, 0, 0, 1}}},
    {11, {5, 0, {0, 0, 0, 1}}},
    {12, {5, 0, {0, 0, 0, 1}}},
    {13, {5, 0, {0, 0, 0, 1}}},
    {14, {5, 0, {0, 0, 0, 1}}},
    {15, {5, 0, {0, 0, 0, 1}}},
    {16, {5, 0, {0, 0, 0, 1}}},
    {17, {5, 0, {0, 0, 0, 1}}},
    {18, {5, 0, {0, 0, 0, 1}}},
    {19, {5, 0, {0, 0, 0, 1}}},
    {20, {5, 0, {0, 0, 0, 1}}},
    {21, {0, 2, {1, 0, 0, 0}}},
    {22, {0, 2, {1, 0, 0, 0}}},
    {23, {0, 2, {1, 0, 0, 0}}},
    {24, {0, 2, {1, 0, 0, 0}}},
    {25, {0, 2, {1, 0, 0, 0}}},
    {26, {0, 2, {1, 0, 0, 0}}},
    {27, {0, 2, {1, 0, 0, 0}}},
    {28, {0, 2, {1, 0, 0, 0}}},
    {29, {0, 2, {1, 0, 0, 0}}},
    {30, {0, 2, {1, 0, 0, 0}}},
    {31, {0, 2, {1, 0, 0, 0}}},
    {32, {0, 2, {1, 0, 0, 0}}},
    {33, {0, 2, {1, 0, 0, 0}}},
    {34, {0, 2, {1, 0, 0, 0}}},
    {35, {0, 2, {1, 0, 0, 0}}},
    {36, {0, 2, {1, 0, 0, 0}}},
    {37, {0, 2, {1, 0, 0, 0}}},
    {38, {0, 2, {1, 0, 0, 0}}},
    {39, {0, 1, {1, 0, 0, 0}}},
    {40, {0, 1, {1, 0, 0, 0}}},
    {41, {0, 1, {1, 0, 0, 0}}},
    {42, {0, 1, {1, 0, 0, 0}}},
    {43, {0, 1, {1, 0, 0, 0}}},
    {44, {0, 1, {1, 0, 0, 0}}},
    {45, {0, 1, {1, 0, 0, 0}}},
    {46, {0, 1, {1, 0, 0, 0}}},
    {47, {0, 1, {1, 0, 0, 0}}},
    {48, {0, 1, {1, 0, 0, 0}}},
    {49, {0, 1, {1, 0, 0, 0}}},
    {50, {0, 1, {1, 0, 0, 0}}},
    {51, {0, 1, {1, 0, 0, 0}}},
    {52, {0, 1, {1, 0, 0, 0}}},
    {53, {0, 1, {1, 0, 0, 0}}},
    {54, {0, 1, {1, 0, 0, 0}}},
    {55, {0, 2, {1, 0, 0, 0}}},
    {56, {0, 2, {1, 0, 0, 0}}},
    {57, {0, 2, {1, 0, 0, 0}}},
    {58, {0, 2, {1, 0, 0, 0}}},
    {59, {0, 2, {1, 0, 0, 0}}},
    {60, {0, 1, {1, 0, 0, 0}}},
    {61, {0, 1, {1, 0, 0, 0}}},
    {62, {0, 1, {1, 0, 0, 0}}},
    {63, {0, 1, {1, 0, 0, 0}}},
    {64, {0, 1, {1, 0, 0, 0}}},
    {65, {0, 1, {1, 0, 0, 0}}},
    {66, {0, 1, {1, 0, 0, 0}}},
    {67, {0, 1, {1, 0, 0, 0}}},
    {68, {0, 1, {1, 0, 0, 0}}},
    {69, {0, 36, {36, 0, 0, 0}}},
    {70, {0, 36, {36, 0, 0, 0}}},
    {71, {0, 5, {5, 0, 0, 0}}},
    {72, {0, 5, {5, 0, 0, 0}}},
    {73, {0, 5, {5, 0, 0, 0}}},
    {74, {0, 5, {5, 0, 0, 0}}},
    {75, {0, 1, {1, 0, 0, 0}}},
    {76, {0, 1, {1, 0, 0, 0}}},
    {77, {0, 1, {1, 0, 0, 0}}},
    {78, {0, 1, {1, 0, 0, 0}}},
    {79, {0, 1, {1, 0, 0, 0}}},
    {80, {0, 1, {1, 0, 0, 0}}},
    {81, {0, 1, {1, 0, 0, 0}}},
    {82, {0, 3, {1, 0, 0, 0}}},
    {83, {0, 3, {1, 0, 0, 0}}},
    {84, {0, 3, {1, 0, 0, 0}}},
    {85, {0, 3, {1, 0, 0, 0}}},
    {86, {0, 1, {1, 0, 0, 0}}},
    {87, {0, 1, {1, 0, 0, 0}}},
    {88, {0, 1, {1, 0, 0, 0}}},
    {89, {0, 1, {1, 0, 0, 0}}},
    {90, {0, 1, {1, 0, 0, 0}}},
    {91, {0, 1, {1, 0, 0, 0}}},
    {92, {0, 1, {1, 0, 0, 0}}},
    {93, {0, 1, {1, 0, 0, 0}}},
    {94, {0, 1, {1, 0, 0, 0}}},
    {95, {0, 1, {1, 0, 0, 0}}},
    {96, {0, 1, {1, 0, 0, 0}}},
    {97, {0, 1, {1, 0, 0, 0}}},
    {98, {0, 1, {1, 0, 0, 0}}},
    {99, {0, 1, {1, 0, 0, 0}}},
    {100, {0, 1, {1, 0, 0, 0}}},
    {101, {0, 1, {1, 0, 0, 0}}},
    {102, {0, 1, {1, 0, 0, 0}}},
    {103, {0, 1, {1, 0, 0, 0}}},
    {104, {0, 1, {1, 0, 0, 0}}},
    {105, {0, 1, {1, 0, 0, 0}}},
    {106, {0, 1, {1, 0, 0, 0}}},
    {107, {0, 1, {1, 0, 0, 0}}},
    {108, {0, 1, {1, 0, 0, 0}}},
    {109, {0, 1, {1, 0, 0, 0}}},
    {110, {0, 1, {1, 0, 0, 0}}},
    {111, {0, 1, {1, 0, 0, 0}}},
    {112, {0, 1, {1, 0, 0, 0}}},
    {113, {0, 1, {1, 0, 0, 0}}},
    {114, {0, 1, {1, 0, 0, 0}}},
    {115, {0, 1, {1, 0, 0, 0}}},
    {116, {0, 1, {1, 0, 0, 0}}},
    {117, {0, 1, {1, 0, 0, 0}}},
    {118, {0, 1, {1, 0, 0, 0}}},
    {119, {0, 4, {1, 0, 0, 0}}},
    {120, {0, 4, {1, 0, 0, 0}}},
    {121, {0, 4, {1, 0, 0, 0}}},
    {122, {0, 2, {1, 0, 0, 0}}},
    {123, {0, 1, {0, 0, 0, 0}}},
    {124, {0, 1, {0, 0, 0, 0}}},
    {125, {0, 1, {0, 0, 0, 0}}},
    {126, {0, 1, {0, 0, 0, 0}}},
    {127, {0, 1, {1, 0, 0, 0}}},
    {128, {0, 1, {1, 0, 0, 0}}},
    {129, {0, 1, {1, 0, 0, 0}}},
    {130, {0, 1, {1, 0, 0, 0}}},
    {131, {1, 4, {1, 1, 1, 1}}},
    {132, {1, 4, {1, 1, 1, 1}}},
    {133, {7, 1, {1, 0, 0, 1}}},
    {134, {7, 1, {1, 0, 0, 1}}},
    {135, {7, 1, {1, 0, 0, 1}}},
    {136, {7, 0, {0, 0, 0, 1}}},
    {137, {0, 1, {1, 0, 0, 0}}},
    {138, {0, 1, {1, 0, 0, 0}}},
    {139, {0, 1, {1, 0, 0, 0}}},
    {140, {0, 1, {1, 0, 0, 0}}},
    {141, {0, 1, {1, 0, 0, 0}}},
    {142, {0, 3, {1, 0, 0, 0}}},
    {143, {0, 3, {1, 0, 0, 0}}},
    {144, {0, 3, {1, 0, 0, 0}}},
    {145, {0, 3, {1, 0, 0, 0}}},
    {146, {0, 3, {1, 0, 0, 0}}},
    {147, {0, 3, {1, 0, 0, 0}}},
    {148, {0, 3, {1, 0, 0, 0}}},
    {149, {0, 3, {1, 0, 0, 0}}},
    {150, {0, 1, {1, 0, 0, 0}}},
    {151, {0, 1, {1, 0, 0, 0}}},
    {152, {0, 1, {1, 0, 0, 0}}},
    {153, {0, 1, {1, 0, 0, 0}}},
    {154, {0, 1, {1, 0, 0, 0}}},
    {155, {0, 1, {1, 0, 0, 0}}},
    {156, {0, 1, {1, 0, 0, 0}}},
    {157, {0, 1, {1, 0, 0, 0}}},
    {158, {1, 4, {1, 1, 1, 1}}},
    {159, {1, 4, {1, 1, 1, 1}}},
    {160, {1, 4, {1, 1, 1, 1}}},
    {161, {1, 4, {1, 1, 1, 1}}},
    {162, {1, 4, {1, 1, 1, 1}}},
    {163, {1, 4, {1, 1, 1, 1}}},
    {164, {1, 4, {1, 1, 1, 1}}},
    {165, {1, 4, {1, 1, 1, 1}}},
    {166, {1, 5, {1, 1, 2, 1}}},
    {167, {1, 4, {1, 1, 1, 1}}},
    {168, {1, 31, {1, 1, 28, 1}}},
    {169, {1, 17, {1, 1, 14, 1}}},
    {170, {1, 5, {1, 1, 2, 1}}},
    {171, {1, 4, {1, 1, 1, 1}}},
    {172, {1, 5, {1, 1, 2, 1}}},
    {173, {1, 4, {1, 1, 1, 1}}},
    {174, {1, 5, {1, 1, 2, 1}}},
    {175, {1, 4, {1, 1, 1, 1}}},
    {176, {1, 5, {1, 1, 2, 1}}},
    {177, {1, 4, {1, 1, 1, 1}}},
    {178, {1, 4, {1, 1, 1, 1}}},
    {179, {1, 4, {1, 1, 1, 1}}},
    {180, {1, 4, {1, 1, 1, 1}}},
    {181, {1, 4, {1, 1, 1, 1}}},
    {182, {1, 4, {1, 1, 1, 1}}},
    {183, {1, 4, {1, 1, 1, 1}}},
    {184, {1, 6, {1, 1, 1, 1}}},
    {185, {1, 6, {1, 1, 1, 1}}},
    {186, {0, 0, {0, 0, 0, 0}}},
    {187, {0, 0, {0, 0, 0, 0}}},
    {188, {0, 0, {0, 0, 0, 0}}},
    {189, {0, 0, {0, 0, 0, 0}}},
    {190, {0, 0, {0, 0, 0, 0}}},
    {191, {0, 0, {0, 0, 0, 0}}},
    {192, {0, 0, {0, 0, 0, 0}}},
    {193, {0, 0, {0, 0, 0, 0}}},
    {194, {0, 0, {0, 0, 0, 0}}},
    {195, {0, 0, {0, 0, 0, 0}}},
    {196, {0, 0, {0, 0, 0, 0}}},
    {197, {0, 0, {0, 0, 0, 0}}},
    {198, {0, 0, {0, 0, 0, 0}}},
    {199, {0, 0, {0, 0, 0, 0}}},
    {200, {0, 0, {0, 0, 0, 0}}},
    {201, {0, 0, {0, 0, 0, 0}}},
    {202, {0, 0, {0, 0, 0, 0}}},
    {203, {0, 0, {0, 0, 0, 0}}},
    {204, {0, 0, {0, 0, 0, 0}}},
    {205, {0, 0, {0, 0, 0, 0}}},
    {206, {0, 0, {0, 0, 0, 0}}},
    {207, {7, 0, {0, 0, 0, 0}}},
    {208, {0, 0, {0, 0, 0, 0}}},
    {209, {0, 0, {0, 0, 0, 0}}},
    {210, {0, 0, {0, 0, 0, 0}}},
    {211, {0, 0, {0, 0, 0, 0}}},
    {212, {0, 0, {0, 0, 0, 0}}},
    {213, {0, 0, {0, 0, 0, 0}}},
    {214, {0, 0, {0, 0, 0, 0}}},
    {215, {7, 0, {0, 0, 0, 0}}},
    {216, {7, 0, {0, 0, 0, 0}}},
    {217, {7, 0, {0, 0, 0, 0}}},
    {218, {7, 0, {0, 0, 0, 0}}},
    {219, {0, 0, {0, 0, 0, 0}}},
    {220, {0, 0, {0, 0, 0, 0}}},
    {221, {0, 0, {0, 0, 0, 0}}},
    {222, {0, 0, {0, 0, 0, 0}}},
    {223, {0, 0, {0, 0, 0, 0}}},
    {224, {0, 0, {0, 0, 0, 0}}},
    {226, {0, 0, {0, 0, 0, 0}}},
    {227, {0, 0, {0, 0, 0, 0}}},
    {228, {0, 0, {0, 0, 0, 0}}},
    {229, {0, 0, {0, 0, 0, 0}}},
    {230, {0, 0, {0, 0, 0, 0}}},
    {231, {0, 0, {0, 0, 0, 0}}},
    {232, {0, 0, {0, 0, 0, 0}}},
    {233, {0, 0, {0, 0, 0, 0}}},
    {234, {0, 0, {0, 0, 0, 0}}},
    {235, {0, 0, {0, 0, 0, 0}}},
    {465, {0, 0, {0, 0, 0, 0}}},
    {466, {0, 0, {0, 0, 0, 0}}},
    {467, {0, 0, {0, 0, 0, 0}}},
    {468, {0, 0, {0, 0, 0, 0}}},
    {469, {0, 0, {0, 0, 0, 0}}},
    {470, {0, 0, {0, 0, 0, 0}}},
    {471, {0, 0, {0, 0, 0, 0}}},
    {472, {0, 0, {0, 0, 0, 0}}},
    {473, {0, 0, {0, 0, 0, 0}}},
    {474, {0, 0, {0, 0, 0, 0}}},
    {475, {0, 0, {0, 0, 0, 0}}},
    {476, {0, 0, {0, 0, 0, 0}}},
    {477, {0, 0, {0, 0, 0, 0}}},
    {478, {0, 0, {0, 0, 0, 0}}},
    {479, {0, 0, {0, 0, 0, 0}}},
    {480, {0, 0, {0, 0, 0, 0}}},
    {481, {0, 0, {0, 0, 0, 0}}},
    {482, {0, 0, {0, 0, 0, 0}}},
    {483, {0, 0, {0, 0, 0, 0}}},
    {484, {0, 0, {0, 0, 0, 0}}},
    {485, {0, 0, {0, 0, 0, 0}}},
    {486, {0, 0, {0, 0, 0, 0}}},
    {487, {0, 0, {0, 0, 0, 0}}},
    {488, {0, 0, {0, 0, 0, 0}}},
    {489, {0, 0, {0, 0, 0, 0}}},
    {490, {0, 0, {0, 0, 0, 0}}},
    {491, {0, 0, {0, 0, 0, 0}}},
    {492, {0, 0, {0, 0, 0, 0}}},
};
static char machine601Filename[] = "MachineSimulation601.c";
UInt8 machine601Initialized;
Machine601Info machine601Opcodes[496];
Machine601Stage machine601Pipeline[6];
char machine601Display[46];
extern void CError_Internal(const char *, int);
/* Descriptor slot only: no call or guessed prototype for the shared code entry. */
extern char machineSharedCode[];

void fn_0063cb00(void);
int is_execution_unit_seven(Machine601Instruction *instruction);
void advance_instruction_pipeline(UInt32 clock);
void set_execution_unit_instruction(Machine601Instruction *instruction);
int is_execution_unit_available(Machine601Instruction *instruction);
void clear_instruction_and_globals(void);
int get_latency(Machine601Instruction *instruction);
void fn_0063cf50(UInt8 highlighted);

typedef struct Machine601Descriptor {
    UInt32 header[3];
    void *callbacks[8];
    char *display;
} Machine601Descriptor;

typedef char Machine601DescriptorSize[sizeof(Machine601Descriptor) == 48 ? 1 : -1];
typedef char Machine601DescriptorInitializeOffset[offsetof(Machine601Descriptor, callbacks[7]) == 40 ? 1 : -1];
Machine601Descriptor machine601 = {
    {2, 0, 0},
    {
        (void *)get_latency,
        (void *)clear_instruction_and_globals,
        (void *)is_execution_unit_available,
        (void *)set_execution_unit_instruction,
        (void *)advance_instruction_pipeline,
        (void *)is_execution_unit_seven,
        machineSharedCode,
        (void *)fn_0063cb00
    },
    machine601Display
};

void fn_0063cb00(void)
{
    SInt32 i;
    UInt32 j;
    Machine601Info fallback;
    if (!machine601Initialized) {
        machine601Initialized = 1;
        if (nativeOpcodeTable[0].opcode != 496)
            CError_Internal(machine601Filename, 645);
        fallback = nativeOpcodeTable[0].info;
        for (i = 0; i < 496; ++i)
            machine601Opcodes[i] = fallback;
        for (j = 1; j < 264; ++j)
            machine601Opcodes[nativeOpcodeTable[j].opcode] = nativeOpcodeTable[j].info;
    }
}

int is_execution_unit_seven(Machine601Instruction *instruction)
{
    int unit = machine601Opcodes[instruction->opcode].unit;
    return unit == 7;
}

void advance_instruction_pipeline(UInt32 clock)
{
    SInt32 i;
    for (i = 0; i < 6; ++i) {
        if (machine601Pipeline[i].instruction && machine601Pipeline[i].count)
            --machine601Pipeline[i].count;
    }
    if (machine601Pipeline[0].instruction && !machine601Pipeline[0].count)
        machine601Pipeline[0].instruction = NULL;
    if (machine601Pipeline[4].instruction && !machine601Pipeline[4].count)
        machine601Pipeline[4].instruction = NULL;
    if (machine601Pipeline[5].instruction && !machine601Pipeline[5].count)
        machine601Pipeline[5].instruction = NULL;
    if (machine601Pipeline[3].instruction && !machine601Pipeline[3].count && !machine601Pipeline[4].instruction) {
        machine601Pipeline[4].count = machine601Opcodes[machine601Pipeline[3].instruction->opcode].cycles[3];
        machine601Pipeline[4].instruction = machine601Pipeline[3].instruction;
        machine601Pipeline[3].instruction = NULL;
    }
    if (machine601Pipeline[2].instruction && !machine601Pipeline[2].count && !machine601Pipeline[3].instruction) {
        machine601Pipeline[3].count = machine601Opcodes[machine601Pipeline[2].instruction->opcode].cycles[2];
        machine601Pipeline[3].instruction = machine601Pipeline[2].instruction;
        machine601Pipeline[2].instruction = NULL;
    }
    if (machine601Pipeline[1].instruction && !machine601Pipeline[1].count && !machine601Pipeline[2].instruction) {
        machine601Pipeline[2].count = machine601Opcodes[machine601Pipeline[1].instruction->opcode].cycles[1];
        machine601Pipeline[2].instruction = machine601Pipeline[1].instruction;
        machine601Pipeline[1].instruction = NULL;
    }
}

void set_execution_unit_instruction(Machine601Instruction *instruction)
{
    UInt8 unit = machine601Opcodes[instruction->opcode].unit;
    SInt32 count = machine601Opcodes[instruction->opcode].cycles[0];
    if (unit == 7)
        unit = 0;
    fn_0063cf50(unit);
    machine601Pipeline[unit].instruction = instruction;
    machine601Pipeline[unit].count = count;
}

int is_execution_unit_available(Machine601Instruction *instruction)
{
    SInt32 unit = machine601Opcodes[instruction->opcode].unit;
    if (unit == 7)
        unit = 0;
    if (unit < 6 && machine601Pipeline[unit].instruction)
        return 0;
    return 1;
}

void clear_instruction_and_globals(void)
{
    machine601Pipeline[0].instruction = NULL;
    machine601Pipeline[1].instruction = NULL;
    machine601Pipeline[2].instruction = NULL;
    machine601Pipeline[3].instruction = NULL;
    machine601Pipeline[4].instruction = NULL;
    machine601Pipeline[5].instruction = NULL;
    fn_0063cf50(6);
}

int get_latency(Machine601Instruction *instruction)
{
    int latency = machine601Opcodes[instruction->opcode].latency;
    if (instruction->flags & 0x100000)
        latency += 2;
    if (instruction->opcode == 0x27 || instruction->opcode == 0x36)
        latency += instruction->operandCount - 2;
    return latency;
}

void fn_0063cf50(UInt8 highlighted)
{
    SInt32 i;
    SInt32 offset;
    SInt32 position;
    UInt8 value;
    for (i = 0, offset = 0; i < 6; ++i, offset += 7) {
        machine601Display[offset] = '|';
        value = ' ';
        if (machine601Pipeline[i].instruction)
            value = '|';
        else if (i == highlighted)
            value = '+';
        position = offset;
        machine601Display[++position] = value;
        machine601Display[++position] = value;
        machine601Display[++position] = value;
        machine601Display[++position] = value;
        machine601Display[++position] = value;
        machine601Display[++position] = value;
    }
    machine601Display[42] = '|';
    machine601Display[43] = ' ';
    machine601Display[44] = ':';
    machine601Display[45] = 0;
}
