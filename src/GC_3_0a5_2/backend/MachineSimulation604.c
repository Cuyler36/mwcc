/* MachineSimulation604.c: native member, ABI, descriptor and data review is recorded in the TU ledger. */
#include <stddef.h>
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef short SInt16;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef int SInt32;
#pragma pack(push,2)
typedef struct Machine604Info { UInt8 unit; SInt8 latency; SInt8 cycles[3]; SInt8 serializes; } Machine604Info;
typedef struct Machine604Opcode { SInt16 opcode; Machine604Info info; } Machine604Opcode;
typedef struct Machine604Instruction {
 UInt8 unknown00[12]; UInt32 flags; UInt32 recordFlags; UInt8 unknown14[20]; SInt16 opcode; SInt16 operandCount;
} Machine604Instruction;
typedef struct Machine604Stage { Machine604Instruction * volatile instruction; UInt32 count; } Machine604Stage;
typedef struct Machine604Completion { Machine604Instruction *instruction; UInt32 completed; } Machine604Completion;
#pragma pack(pop)
typedef char NativeInfoSize[sizeof(Machine604Info)==6?1:-1];
typedef char NativeOpcodeSize[sizeof(Machine604Opcode)==8?1:-1];
typedef char NativeInstructionOpcode[offsetof(Machine604Instruction,opcode)==40?1:-1];
typedef char NativeStageSize[sizeof(Machine604Stage)==8?1:-1];
typedef char NativeCompletionSize[sizeof(Machine604Completion)==8?1:-1];
typedef char NativeInstructionFlags[offsetof(Machine604Instruction,flags)==12?1:-1];
typedef char NativeInstructionRecordFlags[offsetof(Machine604Instruction,recordFlags)==16?1:-1];
typedef char NativeInstructionOperandCount[offsetof(Machine604Instruction,operandCount)==42?1:-1];
static Machine604Opcode nativeOpcodeTable[223] = {
 {496,{2,1,{1,0,0},1}},
 {0,{8,0,{0,0,0},1}},
 {1,{8,0,{0,0,0},1}},
 {2,{8,0,{0,0,0},1}},
 {3,{8,0,{0,0,0},1}},
 {4,{8,0,{0,0,0},1}},
 {5,{8,0,{0,0,0},1}},
 {6,{8,0,{0,0,0},1}},
 {7,{8,0,{0,0,0},1}},
 {8,{8,0,{0,0,0},1}},
 {9,{8,0,{0,0,0},1}},
 {10,{8,0,{0,0,0},1}},
 {11,{8,0,{0,0,0},1}},
 {12,{8,0,{0,0,0},1}},
 {13,{8,0,{0,0,0},1}},
 {14,{8,0,{0,0,0},1}},
 {15,{8,0,{0,0,0},1}},
 {16,{8,0,{0,0,0},1}},
 {17,{8,0,{0,0,0},1}},
 {18,{8,0,{0,0,0},1}},
 {19,{8,0,{0,0,0},1}},
 {20,{8,0,{0,0,0},1}},
 {21,{6,2,{1,1,0},0}},
 {22,{6,2,{1,1,0},0}},
 {23,{6,2,{1,1,0},0}},
 {24,{6,2,{1,1,0},0}},
 {25,{6,2,{1,1,0},0}},
 {26,{6,2,{1,1,0},0}},
 {27,{6,2,{1,1,0},0}},
 {28,{6,2,{1,1,0},0}},
 {29,{6,2,{1,1,0},0}},
 {30,{6,2,{1,1,0},0}},
 {31,{6,2,{1,1,0},0}},
 {32,{6,2,{1,1,0},0}},
 {33,{6,2,{1,1,0},0}},
 {34,{6,2,{1,1,0},0}},
 {35,{6,2,{1,1,0},0}},
 {36,{6,2,{1,1,0},0}},
 {37,{6,2,{1,1,0},0}},
 {38,{6,2,{1,1,0},0}},
 {39,{6,2,{1,1,0},0}},
 {40,{6,3,{1,1,0},0}},
 {41,{6,3,{1,1,0},0}},
 {42,{6,3,{1,1,0},0}},
 {43,{6,3,{1,1,0},0}},
 {44,{6,3,{1,1,0},0}},
 {45,{6,3,{1,1,0},0}},
 {46,{6,3,{1,1,0},0}},
 {47,{6,3,{1,1,0},0}},
 {48,{6,3,{1,1,0},0}},
 {49,{6,3,{1,1,0},0}},
 {50,{6,3,{1,1,0},0}},
 {51,{6,3,{1,1,0},0}},
 {52,{6,3,{1,1,0},0}},
 {53,{6,3,{1,1,0},0}},
 {54,{6,2,{1,1,0},0}},
 {55,{6,2,{1,1,0},0}},
 {56,{6,2,{1,1,0},0}},
 {57,{6,2,{1,1,0},0}},
 {58,{6,2,{1,1,0},0}},
 {59,{6,2,{1,1,0},0}},
 {60,{0,1,{1,0,0},0}},
 {61,{0,1,{1,0,0},0}},
 {62,{0,1,{1,0,0},0}},
 {63,{0,1,{1,0,0},0}},
 {64,{0,1,{1,0,0},0}},
 {65,{0,1,{1,0,0},0}},
 {66,{0,1,{1,0,0},0}},
 {67,{0,1,{1,0,0},0}},
 {68,{0,1,{1,0,0},0}},
 {69,{2,20,{20,0,0},0}},
 {70,{2,20,{20,0,0},0}},
 {71,{2,4,{4,0,0},0}},
 {72,{2,4,{4,0,0},0}},
 {73,{2,3,{3,0,0},0}},
 {74,{2,4,{4,0,0},0}},
 {75,{0,1,{1,0,0},0}},
 {76,{0,1,{1,0,0},0}},
 {77,{0,1,{1,0,0},0}},
 {78,{0,1,{1,0,0},0}},
 {79,{0,1,{1,0,0},0}},
 {80,{0,1,{1,0,0},0}},
 {81,{0,1,{1,0,0},0}},
 {82,{0,3,{1,0,0},0}},
 {83,{0,3,{1,0,0},0}},
 {84,{0,3,{1,0,0},0}},
 {85,{0,3,{1,0,0},0}},
 {86,{0,1,{1,0,0},0}},
 {87,{0,1,{1,0,0},0}},
 {88,{0,1,{1,0,0},0}},
 {89,{0,1,{1,0,0},0}},
 {90,{0,1,{1,0,0},0}},
 {91,{0,1,{1,0,0},0}},
 {92,{0,1,{1,0,0},0}},
 {93,{0,1,{1,0,0},0}},
 {94,{0,1,{1,0,0},0}},
 {95,{0,1,{1,0,0},0}},
 {96,{0,1,{1,0,0},0}},
 {97,{0,1,{1,0,0},0}},
 {98,{0,1,{1,0,0},0}},
 {99,{0,1,{1,0,0},0}},
 {100,{0,1,{1,0,0},0}},
 {101,{0,1,{1,0,0},0}},
 {102,{0,1,{1,0,0},0}},
 {103,{0,1,{1,0,0},0}},
 {104,{0,1,{1,0,0},0}},
 {105,{0,1,{1,0,0},0}},
 {106,{0,1,{1,0,0},0}},
 {107,{0,1,{1,0,0},0}},
 {108,{0,1,{1,0,0},0}},
 {109,{0,1,{1,0,0},0}},
 {110,{8,1,{1,0,0},0}},
 {111,{8,1,{1,0,0},0}},
 {112,{8,1,{1,0,0},0}},
 {113,{8,1,{1,0,0},0}},
 {114,{8,1,{1,0,0},0}},
 {115,{8,1,{1,0,0},0}},
 {116,{8,1,{1,0,0},0}},
 {117,{8,1,{1,0,0},0}},
 {118,{8,1,{1,0,0},0}},
 {119,{2,1,{1,0,0},0}},
 {120,{2,1,{1,0,0},0}},
 {121,{2,1,{1,0,0},0}},
 {122,{2,1,{1,0,0},0}},
 {123,{2,1,{1,0,0},0}},
 {124,{2,1,{1,0,0},0}},
 {125,{2,1,{1,0,0},0}},
 {126,{2,1,{1,0,0},0}},
 {127,{2,3,{3,0,0},0}},
 {128,{2,3,{3,0,0},0}},
 {129,{2,3,{3,0,0},0}},
 {130,{2,3,{3,0,0},0}},
 {131,{3,3,{1,1,1},0}},
 {132,{3,3,{1,1,1},0}},
 {133,{6,1,{0,0,0},1}},
 {134,{6,1,{0,0,0},1}},
 {135,{6,1,{0,0,0},1}},
 {136,{6,1,{1,0,0},1}},
 {137,{0,1,{1,0,0},0}},
 {138,{0,1,{1,0,0},0}},
 {139,{0,1,{1,0,0},0}},
 {140,{0,1,{1,0,0},0}},
 {141,{0,1,{1,0,0},0}},
 {142,{6,3,{1,1,0},0}},
 {143,{6,3,{1,1,0},0}},
 {144,{6,3,{1,1,0},0}},
 {145,{6,3,{1,1,0},0}},
 {146,{6,3,{1,1,0},0}},
 {147,{6,3,{1,1,0},0}},
 {148,{6,3,{1,1,0},0}},
 {149,{6,3,{1,1,0},0}},
 {150,{6,3,{1,1,0},0}},
 {151,{6,3,{1,1,0},0}},
 {152,{6,3,{1,1,0},0}},
 {153,{6,3,{1,1,0},0}},
 {154,{6,3,{1,1,0},0}},
 {155,{6,3,{1,1,0},0}},
 {156,{6,3,{1,1,0},0}},
 {157,{6,3,{1,1,0},0}},
 {158,{3,3,{1,1,1},0}},
 {159,{3,3,{1,1,1},0}},
 {160,{3,3,{1,1,1},0}},
 {161,{3,3,{1,1,1},0}},
 {162,{3,3,{1,1,1},0}},
 {163,{3,3,{1,1,1},0}},
 {164,{3,3,{1,1,1},0}},
 {165,{3,3,{1,1,1},0}},
 {166,{3,3,{1,1,1},0}},
 {167,{3,3,{1,1,1},0}},
 {168,{3,32,{32,0,0},0}},
 {169,{3,18,{18,0,0},0}},
 {170,{3,3,{1,1,1},0}},
 {171,{3,3,{1,1,1},0}},
 {172,{3,3,{1,1,1},0}},
 {173,{3,3,{1,1,1},0}},
 {174,{3,3,{1,1,1},0}},
 {175,{3,3,{1,1,1},0}},
 {176,{3,3,{1,1,1},0}},
 {177,{3,3,{1,1,1},0}},
 {178,{3,18,{18,0,0},0}},
 {179,{3,3,{1,1,1},0}},
 {180,{3,3,{1,1,1},0}},
 {181,{3,3,{1,1,1},0}},
 {182,{3,3,{1,1,1},0}},
 {183,{3,3,{1,1,1},0}},
 {184,{3,5,{1,1,1},0}},
 {185,{3,5,{1,1,1},0}},
 {186,{6,1,{1,0,0},0}},
 {187,{6,1,{1,0,0},0}},
 {188,{6,1,{1,0,0},0}},
 {189,{6,1,{1,0,0},0}},
 {190,{6,1,{1,0,0},0}},
 {191,{6,1,{1,0,0},0}},
 {192,{6,1,{1,0,0},0}},
 {193,{2,1,{1,0,0},1}},
 {194,{2,1,{1,0,0},1}},
 {195,{2,1,{1,0,0},0}},
 {196,{2,1,{1,0,0},0}},
 {197,{2,1,{1,0,0},0}},
 {198,{2,1,{1,0,0},0}},
 {199,{2,1,{1,0,0},0}},
 {200,{2,1,{1,0,0},0}},
 {201,{2,1,{1,0,0},0}},
 {202,{2,1,{1,0,0},0}},
 {203,{2,1,{1,0,0},0}},
 {204,{2,1,{1,0,0},0}},
 {205,{2,1,{1,0,0},0}},
 {206,{2,1,{1,0,0},0}},
 {207,{2,1,{1,0,0},1}},
 {208,{3,1,{1,0,0},0}},
 {209,{3,1,{1,0,0},0}},
 {210,{2,1,{1,0,0},0}},
 {211,{2,1,{1,0,0},0}},
 {212,{2,1,{1,0,0},0}},
 {213,{2,1,{1,0,0},0}},
 {214,{2,1,{1,0,0},0}},
 {215,{2,1,{1,0,0},1}},
 {216,{2,1,{1,0,0},1}},
 {217,{2,1,{1,0,0},1}},
 {218,{2,1,{1,0,0},1}},
 {219,{2,1,{1,0,0},0}},
 {220,{2,1,{1,0,0},1}},
 {221,{2,1,{1,0,0},1}},
};
static UInt8 machine604Initialized;
static Machine604Info machine604Opcodes[496];
#pragma pack(push,2)
typedef struct Machine604CompletionBuffers {
 SInt32 available,pending;UInt32 retireIndex,issueIndex;
 Machine604Completion entries[16];
} Machine604CompletionBuffers;
#pragma pack(pop)
typedef char NativeCompletionBuffersSize[sizeof(Machine604CompletionBuffers)==144?1:-1];
typedef char NativeCompletionBuffersEntries[offsetof(Machine604CompletionBuffers,entries)==16?1:-1];
typedef char NativeCompletionBuffersPending[offsetof(Machine604CompletionBuffers,pending)==4?1:-1];
typedef char NativeCompletionBuffersRetire[offsetof(Machine604CompletionBuffers,retireIndex)==8?1:-1];
typedef char NativeCompletionBuffersIssue[offsetof(Machine604CompletionBuffers,issueIndex)==12?1:-1];
static Machine604CompletionBuffers completionbuffers;
static Machine604Instruction *sciu2_completed_instruction;
static Machine604Instruction *sciu_completed_instruction;
static Machine604Stage pipeline[9];
static char machine604Display[52];
extern char machineSharedCode[]; /* Address import only; no guessed callable prototype. */
extern int fn_00599530(Machine604Instruction *instruction,Machine604Instruction *previous,UInt8 registerClass);
void fn_0063b910(void);
static int serializes(Machine604Instruction *instruction);
static void advance_clock(UInt32 clock);
static void issue(Machine604Instruction *instruction);
static int can_issue(Machine604Instruction *instruction);
static void initialize(void);
static int latency(Machine604Instruction *instruction);
void fn_0063c130(void);

typedef struct Machine604Descriptor {
 UInt32 header[3];
 int (*latency)(Machine604Instruction *);
 void (*reset)(void);
 int (*canIssue)(Machine604Instruction *);
 void (*issue)(Machine604Instruction *);
 void (*advanceClock)(UInt32);
 int (*serializes)(Machine604Instruction *);
 void *sharedCode;
 void (*initialize)(void);
 char *display;
} Machine604Descriptor;
typedef char NativeDescriptorSize[sizeof(Machine604Descriptor)==48?1:-1];
typedef char NativeDescriptorCallbacks[offsetof(Machine604Descriptor,latency)==12?1:-1];
typedef char NativeDescriptorDisplay[offsetof(Machine604Descriptor,display)==44?1:-1];
Machine604Descriptor machine604 = {
 {4,1,0},latency,initialize,can_issue,issue,advance_clock,serializes,machineSharedCode,fn_0063b910,machine604Display
};

void fn_0063b910(void)
{
 SInt32 i;
 UInt32 j;
 Machine604Info fallback;
 if(!machine604Initialized){
  machine604Initialized=1;
  fallback=nativeOpcodeTable[0].info;
  for(i=0;i<496;++i)machine604Opcodes[i]=fallback;
  for(j=1;;){machine604Opcodes[nativeOpcodeTable[j].opcode]=nativeOpcodeTable[j].info;if(++j>=223)break;}
  return;
 }
}

static int serializes(Machine604Instruction *instruction)
{
 return machine604Opcodes[instruction->opcode].serializes;
}

static inline void complete_instruction(Machine604Instruction *instruction)
{
 SInt32 i;
 /* Every active instruction has a live slot in the completion ring. */
 for(i=0;i<16 && completionbuffers.entries[i].instruction!=instruction;++i);
 completionbuffers.entries[i].completed=1;
}

static void advance_clock(UInt32 clock)
{
 SInt32 i,retiredCount,cycles;
 Machine604Instruction *instruction;
 sciu_completed_instruction=0;
 sciu2_completed_instruction=0;
 for(i=0;i<9;++i){
  if(pipeline[i].instruction && pipeline[i].count)--pipeline[i].count;
 }
 retiredCount=0;
 do{
  if(completionbuffers.pending==0)break;
  if(completionbuffers.entries[completionbuffers.retireIndex].completed==0)break;
  completionbuffers.entries[completionbuffers.retireIndex].instruction=0;
  --completionbuffers.pending;++completionbuffers.available;
  completionbuffers.retireIndex=(completionbuffers.retireIndex+1U)&15U;
  ++retiredCount;
 }while(retiredCount<5);
 if(pipeline[0].instruction && pipeline[0].count==0){
  instruction=pipeline[0].instruction;
  complete_instruction(instruction);pipeline[0].instruction=0;
  sciu_completed_instruction=instruction;
 }
 if(pipeline[1].instruction && pipeline[1].count==0){
  Machine604Instruction *instruction;
  instruction=pipeline[1].instruction;
  complete_instruction(instruction);pipeline[1].instruction=0;
  sciu2_completed_instruction=instruction;
 }
 if(pipeline[2].instruction && pipeline[2].count==0){complete_instruction(pipeline[2].instruction);pipeline[2].instruction=0;}
 if(pipeline[7].instruction && pipeline[7].count==0){complete_instruction(pipeline[7].instruction);pipeline[7].instruction=0;}
 if(pipeline[5].instruction && pipeline[5].count==0){complete_instruction(pipeline[5].instruction);pipeline[5].instruction=0;}
 if(pipeline[8].instruction && pipeline[8].count==0){complete_instruction(pipeline[8].instruction);pipeline[8].instruction=0;}
 instruction=pipeline[3].instruction;
 if(instruction && pipeline[3].count==0 && (instruction->opcode==168 || instruction->opcode==169)){
  complete_instruction(pipeline[3].instruction);pipeline[3].instruction=0;
 }
 if(pipeline[4].instruction && pipeline[4].count==0 && pipeline[5].instruction==0){
  instruction=pipeline[4].instruction;
  cycles=machine604Opcodes[instruction->opcode].cycles[2];
  pipeline[5].instruction=instruction;
  pipeline[5].count=cycles;
  pipeline[4].instruction=0;
 }
 if(pipeline[3].instruction && pipeline[3].count==0 && pipeline[4].instruction==0){
  instruction=pipeline[3].instruction;
  cycles=machine604Opcodes[instruction->opcode].cycles[1];
  pipeline[4].instruction=instruction;
  pipeline[4].count=cycles;
  pipeline[3].instruction=0;
 }
 if(pipeline[6].instruction && pipeline[6].count==0 && pipeline[7].instruction==0){
  SInt32 cycles;
  instruction=pipeline[6].instruction;
  cycles=machine604Opcodes[instruction->opcode].cycles[1];
  pipeline[7].instruction=instruction;
  pipeline[7].count=cycles;
  pipeline[6].instruction=0;
 }
}

static void issue(Machine604Instruction *instruction)
{
 UInt32 unit=machine604Opcodes[instruction->opcode].unit;
 SInt32 cycles=machine604Opcodes[instruction->opcode].cycles[0];
 fn_0063c130();
 if(unit==0 && pipeline[0].instruction)unit=1;
 ++completionbuffers.pending;--completionbuffers.available;
 completionbuffers.entries[completionbuffers.issueIndex].instruction=instruction;
 completionbuffers.entries[completionbuffers.issueIndex].completed=0;
 completionbuffers.issueIndex=(completionbuffers.issueIndex+1U)&15U;
 pipeline[unit].instruction=instruction;pipeline[unit].count=cycles;
}

static int can_issue(Machine604Instruction *instruction)
{
 UInt32 category;
 Machine604Instruction *candidate,*ref;
 int firstMissing,secondMissing,enabled;
 category=machine604Opcodes[instruction->opcode].unit;
 enabled=completionbuffers.available;
 if(enabled==0)return 0;
 if(category==0){
  firstMissing=!pipeline[0].instruction;
  secondMissing=(candidate=pipeline[1].instruction)==0;
  if(firstMissing==0 && secondMissing==0)return 0;
  if(firstMissing!=0 && secondMissing!=0)return 1;
  if(firstMissing==0)candidate=pipeline[0].instruction;
  if(fn_00599530(instruction,candidate,4))return 0;
  ref=sciu_completed_instruction;
  if(fn_00599530(instruction,ref,4))return 0;
  ref=sciu2_completed_instruction;
  if(fn_00599530(instruction,ref,4))return 0;
 }else if(pipeline[category].instruction)return 0;
 return 1;
}

static void initialize(void)
{
 SInt32 i;
 for(i=0;i<9;++i)pipeline[i].instruction=0;
 completionbuffers.available=16;completionbuffers.pending=0;completionbuffers.retireIndex=0;completionbuffers.issueIndex=0;
 for(i=0;i<16;++i)completionbuffers.entries[i].instruction=0;
 sciu_completed_instruction=0;sciu2_completed_instruction=0;
 fn_0063c130();
}

static int latency(Machine604Instruction *instruction)
{
 SInt32 latency=machine604Opcodes[instruction->opcode].latency;
 if(instruction->recordFlags&0x100000)latency+=2;
 if(instruction->opcode==39 || instruction->opcode==54)latency+=instruction->operandCount-2;
 return latency;
}

void fn_0063c130(void)
{
 SInt32 i=0,offset=0,one=1,two=2;
 SInt32 highlighted=completionbuffers.issueIndex;
 UInt8 value;
 do{
  machine604Display[offset]='|';value=' ';
  if(completionbuffers.entries[i].instruction)value='|';else if(i==highlighted)value='+';
  machine604Display[one]=value;machine604Display[two]=value;
  ++i;offset+=3;one+=3;two+=3;
 }while(i<16);
 machine604Display[48]='|';machine604Display[49]=(char)highlighted+'A';machine604Display[50]=':';machine604Display[51]=0;
}
