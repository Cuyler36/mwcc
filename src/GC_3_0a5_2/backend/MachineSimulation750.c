/* MachineSimulation750.c: native member, ABI, descriptor and data review is recorded in the TU ledger. */
#include <stddef.h>
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef short SInt16;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef int SInt32;
#pragma pack(push,2)
typedef struct Machine750Info { UInt8 unit; SInt8 latency; SInt8 cycles[3]; SInt8 serializes; } Machine750Info;
typedef struct Machine750Opcode { SInt16 opcode; Machine750Info info; } Machine750Opcode;
typedef struct Machine750Instruction {
 UInt8 unknown00[12]; UInt32 flags; UInt32 recordFlags; UInt8 unknown14[20]; SInt16 opcode; SInt16 operandCount;
} Machine750Instruction;
typedef struct Machine750Stage { Machine750Instruction * volatile instruction; UInt32 count; } Machine750Stage;
typedef struct Machine750Completion { Machine750Instruction *instruction; UInt32 completed; } Machine750Completion;
#pragma pack(pop)
typedef char NativeInfoSize[sizeof(Machine750Info)==6?1:-1];
typedef char NativeOpcodeSize[sizeof(Machine750Opcode)==8?1:-1];
typedef char NativeInstructionOpcode[offsetof(Machine750Instruction,opcode)==40?1:-1];
typedef char NativeStageSize[sizeof(Machine750Stage)==8?1:-1];
typedef char NativeCompletionSize[sizeof(Machine750Completion)==8?1:-1];
typedef char NativeInstructionFlags[offsetof(Machine750Instruction,flags)==12?1:-1];
typedef char NativeInstructionRecordFlags[offsetof(Machine750Instruction,recordFlags)==16?1:-1];
typedef char NativeInstructionOperandCount[offsetof(Machine750Instruction,operandCount)==42?1:-1];
static Machine750Opcode nativeOpcodeTable[223] = {
 {496,{1,1,{1,0,0},1}},
 {0,{0,0,{0,0,0},1}},
 {1,{0,0,{0,0,0},1}},
 {2,{0,0,{0,0,0},1}},
 {3,{0,0,{0,0,0},1}},
 {4,{0,0,{0,0,0},1}},
 {5,{0,0,{0,0,0},1}},
 {6,{0,0,{0,0,0},1}},
 {7,{0,0,{0,0,0},1}},
 {8,{0,0,{0,0,0},1}},
 {9,{0,0,{0,0,0},1}},
 {10,{0,0,{0,0,0},1}},
 {11,{0,0,{0,0,0},1}},
 {12,{0,0,{0,0,0},1}},
 {13,{0,0,{0,0,0},1}},
 {14,{0,0,{0,0,0},1}},
 {15,{0,0,{0,0,0},1}},
 {16,{0,0,{0,0,0},1}},
 {17,{0,0,{0,0,0},1}},
 {18,{0,0,{0,0,0},1}},
 {19,{0,0,{0,0,0},1}},
 {20,{0,0,{0,0,0},1}},
 {21,{3,2,{1,1,0},0}},
 {22,{3,2,{1,1,0},0}},
 {23,{3,2,{1,1,0},0}},
 {24,{3,2,{1,1,0},0}},
 {25,{3,2,{1,1,0},0}},
 {26,{3,2,{1,1,0},0}},
 {27,{3,2,{1,1,0},0}},
 {28,{3,2,{1,1,0},0}},
 {29,{3,2,{1,1,0},0}},
 {30,{3,2,{1,1,0},0}},
 {31,{3,2,{1,1,0},0}},
 {32,{3,2,{1,1,0},0}},
 {33,{3,2,{1,1,0},0}},
 {34,{3,2,{1,1,0},0}},
 {35,{3,2,{1,1,0},0}},
 {36,{3,2,{1,1,0},0}},
 {37,{3,2,{1,1,0},0}},
 {38,{3,2,{1,1,0},0}},
 {39,{3,2,{1,1,0},0}},
 {40,{3,2,{1,1,0},0}},
 {41,{3,2,{1,1,0},0}},
 {42,{3,2,{1,1,0},0}},
 {43,{3,2,{1,1,0},0}},
 {44,{3,2,{1,1,0},0}},
 {45,{3,2,{1,1,0},0}},
 {46,{3,2,{1,1,0},0}},
 {47,{3,2,{1,1,0},0}},
 {48,{3,2,{1,1,0},0}},
 {49,{3,2,{1,1,0},0}},
 {50,{3,2,{1,1,0},0}},
 {51,{3,2,{1,1,0},0}},
 {52,{3,2,{1,1,0},0}},
 {53,{3,2,{1,1,0},0}},
 {54,{3,2,{1,1,0},0}},
 {55,{3,3,{1,2,0},0}},
 {56,{3,3,{1,2,0},0}},
 {57,{3,2,{1,1,0},0}},
 {58,{3,2,{1,1,0},0}},
 {59,{3,3,{1,2,0},0}},
 {60,{2,1,{1,0,0},0}},
 {61,{2,1,{1,0,0},0}},
 {62,{2,1,{1,0,0},0}},
 {63,{2,1,{1,0,0},0}},
 {64,{2,1,{1,0,0},0}},
 {65,{2,1,{1,0,0},0}},
 {66,{2,1,{1,0,0},0}},
 {67,{2,1,{1,0,0},0}},
 {68,{2,1,{1,0,0},0}},
 {69,{1,19,{19,0,0},0}},
 {70,{1,19,{19,0,0},0}},
 {71,{1,5,{5,0,0},0}},
 {72,{1,6,{5,0,0},0}},
 {73,{1,3,{3,0,0},0}},
 {74,{1,5,{5,0,0},0}},
 {75,{2,1,{1,0,0},0}},
 {76,{2,1,{1,0,0},0}},
 {77,{2,1,{1,0,0},0}},
 {78,{2,1,{1,0,0},0}},
 {79,{2,1,{1,0,0},0}},
 {80,{2,1,{1,0,0},0}},
 {81,{2,1,{1,0,0},0}},
 {82,{2,3,{1,0,0},0}},
 {83,{2,3,{1,0,0},0}},
 {84,{2,3,{1,0,0},0}},
 {85,{2,3,{1,0,0},0}},
 {86,{2,1,{1,0,0},0}},
 {87,{2,1,{1,0,0},0}},
 {88,{2,1,{1,0,0},0}},
 {89,{2,1,{1,0,0},0}},
 {90,{2,1,{1,0,0},0}},
 {91,{2,1,{1,0,0},0}},
 {92,{2,1,{1,0,0},0}},
 {93,{2,1,{1,0,0},0}},
 {94,{2,1,{1,0,0},0}},
 {95,{2,1,{1,0,0},0}},
 {96,{2,1,{1,0,0},0}},
 {97,{2,1,{1,0,0},0}},
 {98,{2,1,{1,0,0},0}},
 {99,{2,1,{1,0,0},0}},
 {100,{2,1,{1,0,0},0}},
 {101,{2,1,{1,0,0},0}},
 {102,{2,1,{1,0,0},0}},
 {103,{2,1,{1,0,0},0}},
 {104,{2,1,{1,0,0},0}},
 {105,{2,1,{1,0,0},0}},
 {106,{2,1,{1,0,0},0}},
 {107,{2,1,{1,0,0},0}},
 {108,{2,1,{1,0,0},0}},
 {109,{2,1,{1,0,0},0}},
 {110,{8,1,{1,0,0},1}},
 {111,{8,1,{1,0,0},1}},
 {112,{8,1,{1,0,0},1}},
 {113,{8,1,{1,0,0},1}},
 {114,{8,1,{1,0,0},1}},
 {115,{8,1,{1,0,0},1}},
 {116,{8,1,{1,0,0},1}},
 {117,{8,1,{1,0,0},1}},
 {118,{8,1,{1,0,0},1}},
 {119,{8,2,{2,0,0},1}},
 {120,{8,2,{2,0,0},1}},
 {121,{8,2,{2,0,0},1}},
 {122,{8,1,{1,0,0},1}},
 {123,{8,1,{1,0,0},0}},
 {124,{8,1,{1,0,0},1}},
 {125,{8,1,{1,0,0},1}},
 {126,{8,1,{1,0,0},1}},
 {127,{8,1,{1,0,0},1}},
 {128,{8,1,{1,0,0},1}},
 {129,{8,1,{1,0,0},1}},
 {130,{8,1,{1,0,0},1}},
 {131,{5,3,{1,1,1},0}},
 {132,{5,3,{1,1,1},0}},
 {133,{8,1,{1,0,0},1}},
 {134,{8,2,{2,0,0},1}},
 {135,{8,3,{3,0,0},1}},
 {136,{8,1,{1,0,0},1}},
 {137,{2,1,{1,0,0},0}},
 {138,{2,1,{1,0,0},0}},
 {139,{2,1,{1,0,0},0}},
 {140,{2,1,{1,0,0},0}},
 {141,{2,1,{1,0,0},0}},
 {142,{3,2,{1,1,0},0}},
 {143,{3,2,{1,1,0},0}},
 {144,{3,2,{1,1,0},0}},
 {145,{3,2,{1,1,0},0}},
 {146,{3,2,{1,1,0},0}},
 {147,{3,2,{1,1,0},0}},
 {148,{3,2,{1,1,0},0}},
 {149,{3,2,{1,1,0},0}},
 {150,{3,2,{1,1,0},0}},
 {151,{3,2,{1,1,0},0}},
 {152,{3,2,{1,1,0},0}},
 {153,{3,2,{1,1,0},0}},
 {154,{3,2,{1,1,0},0}},
 {155,{3,2,{1,1,0},0}},
 {156,{3,2,{1,1,0},0}},
 {157,{3,2,{1,1,0},0}},
 {158,{5,3,{1,1,1},0}},
 {159,{5,3,{1,1,1},0}},
 {160,{5,3,{1,1,1},0}},
 {161,{5,3,{1,1,1},0}},
 {162,{5,3,{1,1,1},0}},
 {163,{5,3,{1,1,1},0}},
 {164,{5,3,{1,1,1},0}},
 {165,{5,3,{1,1,1},0}},
 {166,{5,4,{2,1,1},0}},
 {167,{5,3,{1,1,1},0}},
 {168,{5,31,{31,0,0},0}},
 {169,{5,17,{17,0,0},0}},
 {170,{5,4,{2,1,1},0}},
 {171,{5,3,{1,1,1},0}},
 {172,{5,4,{2,1,1},0}},
 {173,{5,3,{1,1,1},0}},
 {174,{5,4,{2,1,1},0}},
 {175,{5,3,{1,1,1},0}},
 {176,{5,4,{2,1,1},0}},
 {177,{5,3,{1,1,1},0}},
 {178,{5,10,{10,0,0},0}},
 {179,{5,3,{1,1,1},0}},
 {180,{5,3,{1,1,1},0}},
 {181,{5,3,{1,1,1},0}},
 {182,{5,3,{1,1,1},0}},
 {183,{5,3,{1,1,1},0}},
 {184,{5,3,{1,1,1},0}},
 {185,{5,3,{1,1,1},0}},
 {186,{3,1,{1,0,0},0}},
 {187,{3,1,{1,0,0},0}},
 {188,{3,1,{1,0,0},0}},
 {189,{3,1,{1,0,0},0}},
 {190,{3,1,{1,0,0},0}},
 {191,{3,1,{1,0,0},0}},
 {192,{3,1,{1,0,0},0}},
 {193,{1,1,{1,0,0},1}},
 {194,{1,1,{1,0,0},1}},
 {195,{1,1,{1,0,0},0}},
 {196,{1,1,{1,0,0},0}},
 {197,{1,1,{1,0,0},0}},
 {198,{1,1,{1,0,0},0}},
 {199,{1,1,{1,0,0},0}},
 {200,{1,1,{1,0,0},0}},
 {201,{1,1,{1,0,0},0}},
 {202,{1,1,{1,0,0},0}},
 {203,{1,1,{1,0,0},0}},
 {204,{1,1,{1,0,0},0}},
 {205,{1,1,{1,0,0},0}},
 {206,{1,1,{1,0,0},0}},
 {207,{1,1,{1,0,0},1}},
 {208,{5,1,{1,0,0},0}},
 {209,{5,1,{1,0,0},0}},
 {210,{1,1,{1,0,0},0}},
 {211,{1,1,{1,0,0},0}},
 {212,{1,1,{1,0,0},0}},
 {213,{1,1,{1,0,0},0}},
 {214,{1,1,{1,0,0},0}},
 {215,{1,1,{1,0,0},1}},
 {216,{1,1,{1,0,0},1}},
 {217,{1,1,{1,0,0},1}},
 {218,{1,1,{1,0,0},1}},
 {219,{1,1,{1,0,0},0}},
 {220,{1,1,{1,0,0},1}},
 {221,{1,1,{1,0,0},1}},
};
static Machine750Opcode nativeOpcodeOverrides[38] = {
 {402,{3,2,{1,1,0},0}},
 {403,{3,2,{1,1,0},0}},
 {404,{3,2,{1,1,0},0}},
 {405,{3,2,{1,1,0},0}},
 {406,{3,2,{1,1,0},0}},
 {407,{3,2,{1,1,0},0}},
 {408,{3,2,{1,1,0},0}},
 {409,{3,2,{1,1,0},0}},
 {410,{3,2,{0,0,0},1}},
 {411,{5,3,{1,1,1},0}},
 {412,{5,3,{1,1,1},0}},
 {413,{5,3,{1,1,1},0}},
 {414,{5,3,{1,1,1},0}},
 {415,{5,3,{1,1,1},0}},
 {416,{5,3,{1,1,1},0}},
 {417,{5,3,{1,1,1},0}},
 {418,{5,3,{1,1,1},0}},
 {419,{5,3,{1,1,1},0}},
 {420,{5,3,{1,1,1},0}},
 {421,{5,3,{1,1,1},0}},
 {422,{5,3,{1,1,1},0}},
 {423,{5,3,{1,1,1},0}},
 {424,{5,3,{1,1,1},0}},
 {425,{5,3,{1,1,1},0}},
 {426,{5,3,{1,1,1},0}},
 {427,{5,3,{1,1,1},0}},
 {428,{5,3,{1,1,1},0}},
 {429,{5,3,{1,1,1},0}},
 {430,{5,3,{1,1,1},0}},
 {431,{5,3,{1,1,1},0}},
 {432,{5,3,{1,1,1},0}},
 {433,{5,3,{1,1,1},0}},
 {434,{5,3,{1,1,1},0}},
 {435,{5,3,{1,1,1},0}},
 {436,{5,3,{1,1,1},0}},
 {437,{5,3,{1,1,1},0}},
 {438,{5,3,{1,1,1},0}},
 {439,{5,3,{1,1,1},0}},
};
static char machine750Display[22];
static UInt8 machine750Initialized;
static Machine750Info machine750Opcodes[496];
#pragma pack(push,2)
typedef struct Machine750CompletionBuffers {
 SInt32 available,pending;UInt32 retireIndex,issueIndex;
 Machine750Completion entries[6];
} Machine750CompletionBuffers;
#pragma pack(pop)
typedef char NativeCompletionBuffersSize[sizeof(Machine750CompletionBuffers)==64?1:-1];
typedef char NativeCompletionBuffersEntries[offsetof(Machine750CompletionBuffers,entries)==16?1:-1];
typedef char NativeCompletionBuffersPending[offsetof(Machine750CompletionBuffers,pending)==4?1:-1];
typedef char NativeCompletionBuffersRetire[offsetof(Machine750CompletionBuffers,retireIndex)==8?1:-1];
typedef char NativeCompletionBuffersIssue[offsetof(Machine750CompletionBuffers,issueIndex)==12?1:-1];
static Machine750CompletionBuffers completionbuffers;
static Machine750Instruction *iu2_completed_instruction;
static Machine750Instruction *iu1_completed_instruction;
static Machine750Stage pipeline[9];
extern char machineSharedCode[]; /* Address import only; no guessed callable prototype. */
extern int fn_00599530(Machine750Instruction *instruction,Machine750Instruction *previous,UInt8 registerClass);
void fn_0063c1b0(void);
static int serializes(Machine750Instruction *instruction);
static void advance_clock(UInt32 clock);
static void issue(Machine750Instruction *instruction);
static int can_issue(Machine750Instruction *instruction);
static void initialize(void);
static int latency(Machine750Instruction *instruction);
void fn_0063ca80(void);

typedef struct Machine750Descriptor {
 UInt32 header[3];
 int (*latency)(Machine750Instruction *);
 void (*reset)(void);
 int (*canIssue)(Machine750Instruction *);
 void (*issue)(Machine750Instruction *);
 void (*advanceClock)(UInt32);
 int (*serializes)(Machine750Instruction *);
 void *sharedCode;
 void (*initialize)(void);
 char *display;
} Machine750Descriptor;
typedef char NativeDescriptorSize[sizeof(Machine750Descriptor)==48?1:-1];
typedef char NativeDescriptorCallbacks[offsetof(Machine750Descriptor,latency)==12?1:-1];
typedef char NativeDescriptorDisplay[offsetof(Machine750Descriptor,display)==44?1:-1];
Machine750Descriptor machine750 = {
 {2,1,0},latency,initialize,can_issue,issue,advance_clock,serializes,machineSharedCode,fn_0063c1b0,machine750Display
};

void fn_0063c1b0(void)
{
 SInt32 i;
 UInt32 j,k;
 Machine750Info fallback;
 if(!machine750Initialized){
  machine750Initialized=1;
  fallback=nativeOpcodeTable[0].info;
  for(i=0;i<496;++i)machine750Opcodes[i]=fallback;
  for(j=1;;++j){machine750Opcodes[nativeOpcodeTable[j].opcode]=nativeOpcodeTable[j].info;if(j==222)break;}
  for(k=0;;++k){machine750Opcodes[nativeOpcodeOverrides[k].opcode]=nativeOpcodeOverrides[k].info;if(k==37)break;}
 }
}

static int serializes(Machine750Instruction *instruction)
{
 return machine750Opcodes[instruction->opcode].serializes;
}

static inline void complete_instruction(Machine750Instruction *instruction)
{
 SInt32 i;
 /* Every active instruction has a live slot in the completion ring. */
 for(i=0;i<6 && completionbuffers.entries[i].instruction!=instruction;++i);
 completionbuffers.entries[i].completed=1;
}

static void advance_clock(UInt32 clock)
{
 SInt32 i,cycles;
 Machine750Instruction *instruction;
 iu1_completed_instruction=0;
 iu2_completed_instruction=0;
 for(i=0;i<9;++i){
  if(pipeline[i].instruction && pipeline[i].count)--pipeline[i].count;
 }
 if(completionbuffers.pending && completionbuffers.entries[completionbuffers.retireIndex].completed){
  completionbuffers.entries[completionbuffers.retireIndex].instruction=0;
  --completionbuffers.pending;++completionbuffers.available;
  completionbuffers.retireIndex=(completionbuffers.retireIndex+1U)%6U;
  if(completionbuffers.pending && completionbuffers.entries[completionbuffers.retireIndex].completed){
   completionbuffers.entries[completionbuffers.retireIndex].instruction=0;
   --completionbuffers.pending;++completionbuffers.available;
   completionbuffers.retireIndex=(completionbuffers.retireIndex+1U)%6U;
  }
 }
 if(pipeline[1].instruction && pipeline[1].count==0){
  instruction=pipeline[1].instruction;
  complete_instruction(instruction);pipeline[1].instruction=0;
  iu1_completed_instruction=instruction;
 }
 if(pipeline[4].instruction && pipeline[4].count==0){complete_instruction(pipeline[4].instruction);pipeline[4].instruction=0;}
 if(pipeline[7].instruction && pipeline[7].count==0){complete_instruction(pipeline[7].instruction);pipeline[7].instruction=0;}
 if(pipeline[8].instruction && pipeline[8].count==0){complete_instruction(pipeline[8].instruction);pipeline[8].instruction=0;}
 if(pipeline[0].instruction && pipeline[0].count==0){complete_instruction(pipeline[0].instruction);pipeline[0].instruction=0;}
 if(pipeline[2].instruction && pipeline[2].count==0){
  Machine750Instruction *instruction;
  instruction=pipeline[2].instruction;
  complete_instruction(instruction);pipeline[2].instruction=0;
  iu2_completed_instruction=instruction;
 }
 instruction=pipeline[5].instruction;
 if(instruction && pipeline[5].count==0 && (instruction->opcode==168 || instruction->opcode==169)){
  complete_instruction(pipeline[5].instruction);pipeline[5].instruction=0;
 }
 if(pipeline[6].instruction && pipeline[6].count==0 && pipeline[7].instruction==0){
  instruction=pipeline[6].instruction;
  cycles=machine750Opcodes[instruction->opcode].cycles[2];
  pipeline[7].instruction=instruction;
  pipeline[7].count=cycles;
  pipeline[6].instruction=0;
 }
 if(pipeline[5].instruction && pipeline[5].count==0 && pipeline[6].instruction==0){
  instruction=pipeline[5].instruction;
  cycles=machine750Opcodes[instruction->opcode].cycles[1];
  pipeline[6].instruction=instruction;
  pipeline[6].count=cycles;
  pipeline[5].instruction=0;
 }
 if(pipeline[3].instruction && pipeline[3].count==0 && pipeline[4].instruction==0){
  SInt32 cycles;
  instruction=pipeline[3].instruction;
  cycles=machine750Opcodes[instruction->opcode].cycles[1];
  pipeline[4].instruction=instruction;
  pipeline[4].count=cycles;
  pipeline[3].instruction=0;
 }
}

static void issue(Machine750Instruction *instruction)
{
 UInt32 unit=machine750Opcodes[instruction->opcode].unit;
 SInt32 cycles=machine750Opcodes[instruction->opcode].cycles[0];
 fn_0063ca80();
 if(unit==2 && !pipeline[1].instruction)unit=1;
 ++completionbuffers.pending;--completionbuffers.available;
 completionbuffers.entries[completionbuffers.issueIndex].instruction=instruction;
 completionbuffers.entries[completionbuffers.issueIndex].completed=0;
 completionbuffers.issueIndex=(completionbuffers.issueIndex+1U)%6U;
 pipeline[unit].instruction=instruction;pipeline[unit].count=cycles;
}

static int can_issue(Machine750Instruction *instruction)
{
 SInt32 category;
 Machine750Instruction *first;
 unsigned int firstMissing;
 int secondMissing;
 Machine750Instruction *second,*other;
 if(completionbuffers.available==0)return 0;
 category=machine750Opcodes[instruction->opcode].unit;
 if(category==2){
  firstMissing=(first=pipeline[1].instruction)==0;
  secondMissing=(second=pipeline[2].instruction)==0;
  if(firstMissing==0 && secondMissing==0)return 0;
  if(firstMissing!=0 && secondMissing!=0)return 1;
  if(firstMissing!=0)first=second;
  if(fn_00599530(instruction,first,4))return 0;
  if(fn_00599530(instruction,iu1_completed_instruction,4))return 0;
  if(fn_00599530(instruction,iu2_completed_instruction,4))return 0;
 }else if(pipeline[category].instruction)return 0;
 if((instruction->flags&4) && (other=pipeline[4].instruction)!=0 && (other->flags&4))return 0;
 return 1;
}

static void initialize(void)
{
 SInt32 i;
 for(i=0;i<9;++i)pipeline[i].instruction=0;
 completionbuffers.available=6;completionbuffers.pending=0;completionbuffers.retireIndex=0;completionbuffers.issueIndex=0;
 for(i=0;i<6;++i)completionbuffers.entries[i].instruction=0;
 iu1_completed_instruction=0;iu2_completed_instruction=0;
 fn_0063ca80();
}

static int latency(Machine750Instruction *instruction)
{
 SInt32 latency=machine750Opcodes[instruction->opcode].latency;
 if(instruction->recordFlags&0x100000)latency+=2;
 if(instruction->opcode==39 || instruction->opcode==54)latency+=instruction->operandCount-2;
 return latency;
}

void fn_0063ca80(void)
{
 SInt32 i=0,offset=0,one=1,two=2;
 SInt32 highlighted=completionbuffers.issueIndex;
 UInt8 value;
 do{
  machine750Display[offset]='|';value=' ';
  if(completionbuffers.entries[i].instruction)value='|';else if(i==highlighted)value='+';
  machine750Display[one]=value;machine750Display[two]=value;
  ++i;offset+=3;one+=3;two+=3;
 }while(i<6);
 machine750Display[18]='|';machine750Display[19]=(char)highlighted+'A';machine750Display[20]=':';machine750Display[21]=0;
}
