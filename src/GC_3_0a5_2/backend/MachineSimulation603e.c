/* MachineSimulation603e.c: native member, ABI, descriptor and data review is recorded in the TU ledger. */
#include <stddef.h>
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef short SInt16;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef int SInt32;
#pragma pack(push,2)
typedef struct Machine603eInfo { UInt8 unit; SInt8 latency; SInt8 cycles[3]; SInt8 serializes; } Machine603eInfo;
typedef struct Machine603eOpcode { SInt16 opcode; Machine603eInfo info; } Machine603eOpcode;
typedef struct Machine603eInstruction {
 UInt8 unknown00[12]; UInt32 flags; UInt32 recordFlags; UInt8 unknown14[20]; SInt16 opcode; SInt16 operandCount;
} Machine603eInstruction;
typedef struct Machine603eStage { Machine603eInstruction * volatile instruction; UInt32 count; } Machine603eStage;
typedef struct Machine603eCompletion { Machine603eInstruction *instruction; UInt32 completed; } Machine603eCompletion;
#pragma pack(pop)
typedef char NativeInfoSize[sizeof(Machine603eInfo)==6?1:-1];
typedef char NativeOpcodeSize[sizeof(Machine603eOpcode)==8?1:-1];
typedef char NativeInstructionOpcode[offsetof(Machine603eInstruction,opcode)==40?1:-1];
typedef char NativeStageSize[sizeof(Machine603eStage)==8?1:-1];
typedef char NativeCompletionSize[sizeof(Machine603eCompletion)==8?1:-1];
typedef char NativeInstructionFlags[offsetof(Machine603eInstruction,flags)==12?1:-1];
typedef char NativeInstructionRecordFlags[offsetof(Machine603eInstruction,recordFlags)==16?1:-1];
typedef char NativeInstructionOperandCount[offsetof(Machine603eInstruction,operandCount)==42?1:-1];
static Machine603eOpcode nativeOpcodeTable[223] = {
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
 {21,{2,2,{1,1,0},0}},
 {22,{2,2,{1,1,0},0}},
 {23,{2,2,{1,1,0},0}},
 {24,{2,2,{1,1,0},0}},
 {25,{2,2,{1,1,0},0}},
 {26,{2,2,{1,1,0},0}},
 {27,{2,2,{1,1,0},0}},
 {28,{2,2,{1,1,0},0}},
 {29,{2,2,{1,1,0},0}},
 {30,{2,2,{1,1,0},0}},
 {31,{2,2,{1,1,0},0}},
 {32,{2,2,{1,1,0},0}},
 {33,{2,2,{1,1,0},0}},
 {34,{2,2,{1,1,0},0}},
 {35,{2,2,{1,1,0},0}},
 {36,{2,2,{1,1,0},0}},
 {37,{2,2,{1,1,0},0}},
 {38,{2,2,{1,1,0},0}},
 {39,{2,2,{1,1,0},0}},
 {40,{2,2,{1,1,0},0}},
 {41,{2,2,{1,1,0},0}},
 {42,{2,2,{1,1,0},0}},
 {43,{2,2,{1,1,0},0}},
 {44,{2,2,{1,1,0},0}},
 {45,{2,2,{1,1,0},0}},
 {46,{2,2,{1,1,0},0}},
 {47,{2,2,{1,1,0},0}},
 {48,{2,2,{1,1,0},0}},
 {49,{2,2,{1,1,0},0}},
 {50,{2,2,{1,1,0},0}},
 {51,{2,2,{1,1,0},0}},
 {52,{2,2,{1,1,0},0}},
 {53,{2,2,{1,1,0},0}},
 {54,{2,2,{1,1,0},0}},
 {55,{2,2,{1,1,0},0}},
 {56,{2,2,{1,1,0},0}},
 {57,{2,2,{1,1,0},0}},
 {58,{2,2,{1,1,0},0}},
 {59,{2,2,{1,1,0},0}},
 {60,{1,1,{1,0,0},0}},
 {61,{1,1,{1,0,0},0}},
 {62,{1,1,{1,0,0},0}},
 {63,{1,1,{1,0,0},0}},
 {64,{1,1,{1,0,0},0}},
 {65,{1,1,{1,0,0},0}},
 {66,{1,1,{1,0,0},0}},
 {67,{1,1,{1,0,0},0}},
 {68,{1,1,{1,0,0},0}},
 {69,{1,37,{37,0,0},0}},
 {70,{1,37,{37,0,0},0}},
 {71,{1,5,{5,0,0},0}},
 {72,{1,5,{5,0,0},0}},
 {73,{1,3,{3,0,0},0}},
 {74,{1,5,{5,0,0},0}},
 {75,{1,1,{1,0,0},0}},
 {76,{1,1,{1,0,0},0}},
 {77,{1,1,{1,0,0},0}},
 {78,{1,1,{1,0,0},0}},
 {79,{1,1,{1,0,0},0}},
 {80,{1,1,{1,0,0},0}},
 {81,{1,1,{1,0,0},0}},
 {82,{1,3,{1,0,0},0}},
 {83,{1,3,{1,0,0},0}},
 {84,{1,3,{1,0,0},0}},
 {85,{1,3,{1,0,0},0}},
 {86,{1,1,{1,0,0},0}},
 {87,{1,1,{1,0,0},0}},
 {88,{1,1,{1,0,0},0}},
 {89,{1,1,{1,0,0},0}},
 {90,{1,1,{1,0,0},0}},
 {91,{1,1,{1,0,0},0}},
 {92,{1,1,{1,0,0},0}},
 {93,{1,1,{1,0,0},0}},
 {94,{1,1,{1,0,0},0}},
 {95,{1,1,{1,0,0},0}},
 {96,{1,1,{1,0,0},0}},
 {97,{1,1,{1,0,0},0}},
 {98,{1,1,{1,0,0},0}},
 {99,{1,1,{1,0,0},0}},
 {100,{1,1,{1,0,0},0}},
 {101,{1,1,{1,0,0},0}},
 {102,{1,1,{1,0,0},0}},
 {103,{1,1,{1,0,0},0}},
 {104,{1,1,{1,0,0},0}},
 {105,{1,1,{1,0,0},0}},
 {106,{1,1,{1,0,0},0}},
 {107,{1,1,{1,0,0},0}},
 {108,{1,1,{1,0,0},0}},
 {109,{1,1,{1,0,0},0}},
 {110,{7,1,{1,0,0},0}},
 {111,{7,1,{1,0,0},0}},
 {112,{7,1,{1,0,0},0}},
 {113,{7,1,{1,0,0},0}},
 {114,{7,1,{1,0,0},0}},
 {115,{7,1,{1,0,0},0}},
 {116,{7,1,{1,0,0},0}},
 {117,{7,1,{1,0,0},0}},
 {118,{7,1,{1,0,0},0}},
 {119,{7,2,{2,0,0},0}},
 {120,{7,2,{2,0,0},0}},
 {121,{7,2,{2,0,0},0}},
 {122,{7,1,{1,0,0},0}},
 {123,{7,1,{1,0,0},1}},
 {124,{7,1,{1,0,0},1}},
 {126,{7,1,{1,0,0},1}},
 {125,{7,1,{1,0,0},1}},
 {127,{7,1,{1,0,0},0}},
 {128,{7,1,{1,0,0},0}},
 {129,{7,1,{1,0,0},0}},
 {130,{7,1,{1,0,0},0}},
 {131,{4,3,{1,1,1},0}},
 {132,{4,3,{1,1,1},0}},
 {133,{7,1,{1,0,0},1}},
 {134,{7,1,{1,0,0},1}},
 {135,{7,1,{1,0,0},1}},
 {136,{7,1,{1,0,0},1}},
 {137,{1,1,{1,0,0},0}},
 {138,{1,1,{1,0,0},0}},
 {139,{1,1,{1,0,0},0}},
 {140,{1,1,{1,0,0},0}},
 {141,{1,1,{1,0,0},0}},
 {142,{2,2,{1,1,0},0}},
 {143,{2,2,{1,1,0},0}},
 {144,{2,2,{1,1,0},0}},
 {145,{2,2,{1,1,0},0}},
 {146,{2,2,{1,1,0},0}},
 {147,{2,2,{1,1,0},0}},
 {148,{2,2,{1,1,0},0}},
 {149,{2,2,{1,1,0},0}},
 {150,{2,2,{1,1,0},0}},
 {151,{2,2,{1,1,0},0}},
 {152,{2,2,{1,1,0},0}},
 {153,{2,2,{1,1,0},0}},
 {154,{2,2,{1,1,0},0}},
 {155,{2,2,{1,1,0},0}},
 {156,{2,2,{1,1,0},0}},
 {157,{2,2,{1,1,0},0}},
 {158,{4,3,{1,1,1},0}},
 {159,{4,3,{1,1,1},0}},
 {160,{4,3,{1,1,1},0}},
 {161,{4,3,{1,1,1},0}},
 {162,{4,3,{1,1,1},0}},
 {163,{4,3,{1,1,1},0}},
 {164,{4,3,{1,1,1},0}},
 {165,{4,3,{1,1,1},0}},
 {166,{4,4,{2,1,1},0}},
 {167,{4,3,{1,1,1},0}},
 {168,{4,33,{33,0,0},0}},
 {169,{4,18,{18,0,0},0}},
 {170,{4,4,{2,1,1},0}},
 {171,{4,3,{1,1,1},0}},
 {172,{4,4,{2,1,1},0}},
 {173,{4,3,{1,1,1},0}},
 {174,{4,4,{2,1,1},0}},
 {175,{4,3,{1,1,1},0}},
 {176,{4,4,{2,1,1},0}},
 {177,{4,3,{1,1,1},0}},
 {178,{4,18,{18,0,0},0}},
 {179,{4,3,{1,1,1},0}},
 {180,{4,3,{1,1,1},0}},
 {181,{4,3,{1,1,1},0}},
 {182,{4,3,{1,1,1},0}},
 {183,{4,3,{1,1,1},0}},
 {184,{4,5,{1,1,1},0}},
 {185,{4,5,{1,1,1},0}},
 {186,{2,1,{1,0,0},0}},
 {187,{2,1,{1,0,0},0}},
 {188,{2,1,{1,0,0},0}},
 {189,{2,1,{1,0,0},0}},
 {190,{2,1,{1,0,0},0}},
 {191,{2,1,{1,0,0},0}},
 {192,{2,1,{1,0,0},0}},
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
 {208,{4,1,{1,0,0},0}},
 {209,{4,1,{1,0,0},0}},
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
UInt8 machine603eInitialized;
Machine603eInfo machine603eOpcodes[496];

#pragma pack(push,2)
typedef struct Machine603eCompletionBuffers {
 SInt32 available,pending;UInt32 retireIndex,issueIndex;
 Machine603eCompletion completion[5];
} Machine603eCompletionBuffers;
#pragma pack(pop)
typedef char NativeStateSize[sizeof(Machine603eCompletionBuffers)==56?1:-1];
typedef char NativeStatePending[offsetof(Machine603eCompletionBuffers,pending)==4?1:-1];
typedef char NativeStateRetire[offsetof(Machine603eCompletionBuffers,retireIndex)==8?1:-1];
typedef char NativeStateIssue[offsetof(Machine603eCompletionBuffers,issueIndex)==12?1:-1];
typedef char NativeStateCompletion[offsetof(Machine603eCompletionBuffers,completion)==16?1:-1];

Machine603eCompletionBuffers completionbuffers;
Machine603eStage pipeline[8];
char machine603eDisplay[19];
extern int fn_00599530(Machine603eInstruction *instruction, Machine603eInstruction *previous, UInt8 registerClass);
extern char machineSharedCode[]; /* Address import only; no guessed callable prototype. */
void fn_0063b100(void);
static int serializes(Machine603eInstruction *instruction);
static void advance_clock(UInt32 clock);
static void issue(Machine603eInstruction *instruction);
static int can_issue(Machine603eInstruction *instruction);
static void initialize(void);
static int latency(Machine603eInstruction *instruction);
void fn_0063b890(void);
typedef struct Machine603eDescriptor {
 UInt32 header[3];
 int (*latency)(Machine603eInstruction *);
 void (*reset)(void);
 int (*canIssue)(Machine603eInstruction *);
 void (*issue)(Machine603eInstruction *);
 void (*advanceClock)(UInt32);
 int (*serializes)(Machine603eInstruction *);
 void *sharedCode;
 void (*initialize)(void);
 char *display;
} Machine603eDescriptor;
typedef char NativeDescriptorSize[sizeof(Machine603eDescriptor)==48?1:-1];
typedef char NativeDescriptorCallbacks[offsetof(Machine603eDescriptor,latency)==12?1:-1];
typedef char NativeDescriptorDisplay[offsetof(Machine603eDescriptor,display)==44?1:-1];
Machine603eDescriptor machine603e = {
 {2,1,0}, latency,initialize,can_issue,issue,
 advance_clock,serializes,machineSharedCode,fn_0063b100,machine603eDisplay
};

void fn_0063b100(void)
{
 SInt32 i;
 UInt32 j;
 Machine603eInfo fallback;
 if(!machine603eInitialized){
  machine603eInitialized=1;
  fallback=nativeOpcodeTable[0].info;
  for(i=0;i<496;++i)machine603eOpcodes[i]=fallback;
  for(j=1;;){machine603eOpcodes[nativeOpcodeTable[j].opcode]=nativeOpcodeTable[j].info;if(++j>=223)break;}
  return;
 }
}

static int serializes(Machine603eInstruction *instruction)
{
 /* Descriptor serializes callback reads the sixth byte, not the execution-unit byte. */
 return machine603eOpcodes[instruction->opcode].serializes;
}

static inline void RemovePending(Machine603eInstruction *instruction)
{
 SInt32 i;
 /* Every active instruction has a live slot in the completion ring. */
 for(i=0;i<5 && completionbuffers.completion[i].instruction!=instruction;++i);
 completionbuffers.completion[i].completed=1;
}

static void advance_clock(UInt32 clock)
{
 /* Scheduler supplies the current clock; this model advances by one tick. */
 SInt32 i;
 Machine603eInstruction *instruction;
 for(i=0;i<8;++i){
  if(pipeline[i].instruction && pipeline[i].count)--pipeline[i].count;
 }
 if(completionbuffers.pending && completionbuffers.completion[completionbuffers.retireIndex].completed){
  completionbuffers.completion[completionbuffers.retireIndex].instruction=0;
  --completionbuffers.pending;
  ++completionbuffers.available;
  completionbuffers.retireIndex=(completionbuffers.retireIndex+1U)%5U;
  if(completionbuffers.pending && completionbuffers.completion[completionbuffers.retireIndex].completed){
   completionbuffers.completion[completionbuffers.retireIndex].instruction=0;
   --completionbuffers.pending;
   ++completionbuffers.available;
   completionbuffers.retireIndex=(completionbuffers.retireIndex+1U)%5U;
  }
 }
 if(pipeline[1].instruction && pipeline[1].count==0){RemovePending(pipeline[1].instruction);pipeline[1].instruction=0;}
 if(pipeline[3].instruction && pipeline[3].count==0){RemovePending(pipeline[3].instruction);pipeline[3].instruction=0;}
 if(pipeline[6].instruction && pipeline[6].count==0){RemovePending(pipeline[6].instruction);pipeline[6].instruction=0;}
 if(pipeline[7].instruction && pipeline[7].count==0){RemovePending(pipeline[7].instruction);pipeline[7].instruction=0;}
 if(pipeline[0].instruction && pipeline[0].count==0){RemovePending(pipeline[0].instruction);pipeline[0].instruction=0;}
 instruction=pipeline[4].instruction;
 if(instruction && pipeline[4].count==0 && (instruction->opcode==168 || instruction->opcode==169)){
  RemovePending(instruction);pipeline[4].instruction=0;
 }
 if(pipeline[5].instruction && pipeline[5].count==0 && pipeline[6].instruction==0){
  instruction=pipeline[5].instruction;
  pipeline[6].instruction=instruction;
  pipeline[6].count=machine603eOpcodes[instruction->opcode].cycles[2];
  pipeline[5].instruction=0;
 }
 if(pipeline[4].instruction && pipeline[4].count==0 && pipeline[5].instruction==0){
  instruction=pipeline[4].instruction;
  pipeline[5].instruction=instruction;
  pipeline[5].count=machine603eOpcodes[instruction->opcode].cycles[1];
  pipeline[4].instruction=0;
 }
 if(pipeline[2].instruction && pipeline[2].count==0 && pipeline[3].instruction==0){
  instruction=pipeline[2].instruction;
  pipeline[3].instruction=instruction;
  pipeline[3].count=machine603eOpcodes[instruction->opcode].cycles[1];
  pipeline[2].instruction=0;
 }
}

static void issue(Machine603eInstruction *instruction)
{
 UInt32 unit=machine603eOpcodes[instruction->opcode].unit;
 SInt32 cycles=machine603eOpcodes[instruction->opcode].cycles[0];
 fn_0063b890();
 if(unit==1 && pipeline[1].instruction)unit=7;
 ++completionbuffers.pending;--completionbuffers.available;
 completionbuffers.completion[completionbuffers.issueIndex].instruction=instruction;
 completionbuffers.completion[completionbuffers.issueIndex].completed=0;
 completionbuffers.issueIndex=(completionbuffers.issueIndex+1U)%5U;
 pipeline[unit].instruction=instruction;
 pipeline[unit].count=cycles;
}

static int can_issue(Machine603eInstruction *instruction)
{
 UInt32 unit;
 Machine603eInstruction *previous;
 if(completionbuffers.available==0)return 0;
 unit=machine603eOpcodes[instruction->opcode].unit;
 if(pipeline[unit].instruction){
  if(unit==1){
   switch(instruction->opcode){
   case 60:case 61:case 63:case 66:case 82:case 83:case 84:case 85:
    if(fn_00599530(instruction,pipeline[1].instruction,4))return 0;
    if(pipeline[7].instruction==0)return 1;
   }
  }
  return 0;
 }
 if(instruction->flags&4){
  previous=pipeline[3].instruction;
  if(previous && (previous->flags&4))return 0;
 }
 return 1;
}

static void initialize(void)
{
 pipeline[0].instruction=0;pipeline[1].instruction=0;
 pipeline[2].instruction=0;pipeline[3].instruction=0;
 pipeline[4].instruction=0;pipeline[5].instruction=0;
 pipeline[6].instruction=0;pipeline[7].instruction=0;
 completionbuffers.available=5;completionbuffers.pending=0;completionbuffers.retireIndex=0;completionbuffers.issueIndex=0;
 completionbuffers.completion[0].instruction=0;completionbuffers.completion[1].instruction=0;
 completionbuffers.completion[2].instruction=0;completionbuffers.completion[3].instruction=0;completionbuffers.completion[4].instruction=0;
 fn_0063b890();
}

static int latency(Machine603eInstruction *instruction)
{
 SInt32 latency=machine603eOpcodes[instruction->opcode].latency;
 if(instruction->recordFlags&0x100000)latency+=2;
 if(instruction->opcode==39 || instruction->opcode==54)latency+=instruction->operandCount-2;
 return latency;
}

void fn_0063b890(void)
{
 SInt32 i=0,offset=0,one=1,two=2;
 SInt32 highlighted=completionbuffers.issueIndex;
 UInt8 value;
 do{
  machine603eDisplay[offset]='|';
  value=' ';
  if(completionbuffers.completion[i].instruction)value='|';else if(i==highlighted)value='+';
  machine603eDisplay[one]=value;machine603eDisplay[two]=value;
  ++i;offset+=3;one+=3;two+=3;
 }while(i<5);
 machine603eDisplay[15]='|';machine603eDisplay[16]=(char)highlighted+'A';machine603eDisplay[17]=':';machine603eDisplay[18]=0;
}
