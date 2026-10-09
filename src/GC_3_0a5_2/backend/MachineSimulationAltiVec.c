/* MachineSimulationAltiVec.c: native filename, descriptor and packed state. */
#include <stddef.h>
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef short SInt16;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef int SInt32;
#pragma pack(push,2)
typedef struct NativeInfo { UInt8 unit; SInt8 latency; SInt8 cycles[4]; SInt8 serializes; } NativeInfo;
typedef struct NativeOpcode { SInt16 opcode; NativeInfo info; } NativeOpcode;
typedef struct NativeInstruction { UInt8 unknown00[12]; UInt32 flags; UInt32 recordFlags; UInt8 unknown14[20]; SInt16 opcode; SInt16 operandCount; UInt8 operandKind; UInt8 operandClass; } NativeInstruction;
typedef struct NativeStage { NativeInstruction *instruction; SInt32 count; } NativeStage;
typedef struct NativeCompletion { NativeInstruction *instruction; UInt32 completed; } NativeCompletion;
typedef struct NativeCompletionBuffers { UInt32 available; UInt32 pending; UInt32 retireIndex; UInt32 issueIndex; NativeCompletion entries[16]; } NativeCompletionBuffers;
#pragma pack(pop)
typedef char NativeInfoSize[sizeof(NativeInfo)==7?1:-1];
typedef char NativeOpcodeSize[sizeof(NativeOpcode)==10?1:-1];
typedef char NativeInstructionOffset[offsetof(NativeInstruction,opcode)==40?1:-1];
typedef char NativeOperandOffset[offsetof(NativeInstruction,operandKind)==44?1:-1];
typedef char NativeCompletionBuffersSize[sizeof(NativeCompletionBuffers)==144?1:-1];
static NativeOpcode nativeOpcodeTable[401] = {
 {496,{1,1,{1,0,0,0},1}},
 {0,{0,0,{0,0,0,0},0}},
 {1,{0,0,{0,0,0,0},0}},
 {2,{0,0,{0,0,0,0},0}},
 {3,{0,0,{0,0,0,0},0}},
 {4,{0,0,{0,0,0,0},0}},
 {5,{0,0,{0,0,0,0},0}},
 {6,{0,0,{0,0,0,0},0}},
 {7,{0,0,{0,0,0,0},0}},
 {8,{0,0,{0,0,0,0},0}},
 {9,{0,0,{0,0,0,0},0}},
 {10,{0,0,{0,0,0,0},0}},
 {11,{0,0,{0,0,0,0},0}},
 {12,{0,0,{0,0,0,0},0}},
 {13,{0,0,{0,0,0,0},0}},
 {14,{0,0,{0,0,0,0},0}},
 {15,{0,0,{0,0,0,0},0}},
 {16,{0,0,{0,0,0,0},0}},
 {17,{0,0,{0,0,0,0},0}},
 {18,{0,0,{0,0,0,0},0}},
 {19,{0,0,{0,0,0,0},0}},
 {20,{0,0,{0,0,0,0},0}},
 {21,{7,3,{1,1,1,0},0}},
 {22,{7,3,{1,1,1,0},0}},
 {23,{7,3,{1,1,1,0},0}},
 {24,{7,3,{1,1,1,0},0}},
 {25,{7,3,{1,1,1,0},0}},
 {26,{7,3,{1,1,1,0},0}},
 {27,{7,3,{1,1,1,0},0}},
 {28,{7,3,{1,1,1,0},0}},
 {29,{7,3,{1,1,1,0},0}},
 {30,{7,3,{1,1,1,0},0}},
 {31,{7,3,{1,1,1,0},0}},
 {32,{7,3,{1,1,1,0},0}},
 {33,{7,3,{1,1,1,0},0}},
 {34,{7,3,{1,1,1,0},0}},
 {35,{7,3,{1,1,1,0},0}},
 {36,{7,3,{1,1,1,0},0}},
 {37,{7,3,{1,1,1,0},0}},
 {38,{7,3,{1,1,1,0},0}},
 {39,{7,3,{3,0,0,0},0}},
 {40,{7,3,{1,1,1,0},0}},
 {41,{7,3,{1,1,1,0},0}},
 {42,{7,3,{1,1,1,0},0}},
 {43,{7,3,{1,1,1,0},0}},
 {44,{7,3,{1,1,1,0},0}},
 {45,{7,3,{1,1,1,0},0}},
 {46,{7,3,{1,1,1,0},0}},
 {47,{7,3,{1,1,1,0},0}},
 {48,{7,3,{1,1,1,0},0}},
 {49,{7,3,{1,1,1,0},0}},
 {50,{7,3,{1,1,1,0},0}},
 {51,{7,3,{1,1,1,0},0}},
 {52,{7,3,{1,1,1,0},0}},
 {53,{7,3,{1,1,1,0},0}},
 {54,{7,3,{3,0,0,0},0}},
 {55,{7,3,{3,0,0,0},0}},
 {56,{7,3,{3,0,0,0},0}},
 {57,{7,3,{1,1,1,0},0}},
 {58,{7,3,{1,1,1,0},0}},
 {59,{7,3,{1,1,1,0},0}},
 {60,{4,1,{1,0,0,0},0}},
 {61,{4,1,{1,0,0,0},0}},
 {62,{4,1,{1,0,0,0},0}},
 {63,{4,1,{1,0,0,0},0}},
 {64,{4,1,{1,0,0,0},0}},
 {65,{4,1,{1,0,0,0},0}},
 {66,{4,1,{1,0,0,0},0}},
 {67,{4,1,{1,0,0,0},0}},
 {68,{4,1,{1,0,0,0},0}},
 {69,{1,23,{23,0,0,0},0}},
 {70,{1,23,{23,0,0,0},0}},
 {71,{1,4,{2,2,0,0},0}},
 {72,{1,4,{2,2,0,0},0}},
 {73,{1,3,{1,1,1,0},0}},
 {74,{1,4,{2,2,0,0},0}},
 {75,{4,1,{1,0,0,0},0}},
 {76,{4,1,{1,0,0,0},0}},
 {77,{4,1,{1,0,0,0},0}},
 {78,{4,1,{1,0,0,0},0}},
 {79,{4,1,{1,0,0,0},0}},
 {80,{4,1,{1,0,0,0},0}},
 {81,{4,1,{1,0,0,0},0}},
 {82,{4,1,{1,0,0,0},0}},
 {83,{4,1,{1,0,0,0},0}},
 {84,{4,1,{1,0,0,0},0}},
 {85,{4,1,{1,0,0,0},0}},
 {86,{4,1,{1,0,0,0},0}},
 {87,{4,1,{1,0,0,0},0}},
 {88,{4,1,{1,0,0,0},0}},
 {89,{4,1,{1,0,0,0},0}},
 {90,{4,1,{1,0,0,0},0}},
 {91,{4,1,{1,0,0,0},0}},
 {92,{4,1,{1,0,0,0},0}},
 {93,{4,1,{1,0,0,0},0}},
 {94,{4,1,{1,0,0,0},0}},
 {95,{4,1,{1,0,0,0},0}},
 {96,{4,1,{1,0,0,0},0}},
 {97,{4,1,{1,0,0,0},0}},
 {98,{4,1,{1,0,0,0},0}},
 {99,{4,1,{1,0,0,0},0}},
 {100,{4,1,{1,0,0,0},0}},
 {101,{4,1,{1,0,0,0},0}},
 {102,{4,1,{1,0,0,0},0}},
 {103,{4,1,{1,0,0,0},0}},
 {104,{4,1,{1,0,0,0},0}},
 {105,{4,1,{1,0,0,0},0}},
 {106,{4,1,{1,0,0,0},0}},
 {107,{4,1,{1,0,0,0},0}},
 {108,{4,1,{1,0,0,0},0}},
 {109,{4,1,{1,0,0,0},0}},
 {110,{1,2,{2,0,0,0},1}},
 {111,{1,2,{2,0,0,0},1}},
 {112,{1,2,{2,0,0,0},1}},
 {113,{1,2,{2,0,0,0},1}},
 {114,{1,2,{2,0,0,0},1}},
 {115,{1,2,{2,0,0,0},1}},
 {116,{1,2,{2,0,0,0},1}},
 {117,{1,2,{2,0,0,0},1}},
 {118,{1,1,{1,0,0,0},1}},
 {119,{1,2,{2,0,0,0},1}},
 {120,{1,2,{2,0,0,0},1}},
 {121,{1,2,{2,0,0,0},1}},
 {122,{4,1,{1,0,0,0},0}},
 {123,{1,2,{2,0,0,0},1}},
 {124,{1,3,{3,0,0,0},1}},
 {125,{1,3,{2,1,0,0},0}},
 {126,{1,3,{3,0,0,0},1}},
 {127,{1,1,{1,0,0,0},1}},
 {128,{1,1,{1,0,0,0},1}},
 {129,{1,1,{1,0,0,0},1}},
 {130,{1,2,{2,0,0,0},1}},
 {131,{11,5,{5,0,0,0},1}},
 {132,{11,5,{5,0,0,0},1}},
 {133,{7,3,{3,0,0,0},1}},
 {134,{1,1,{1,0,0,0},1}},
 {135,{7,35,{35,0,0,0},1}},
 {136,{1,1,{1,0,0,0},1}},
 {137,{4,1,{1,0,0,0},0}},
 {138,{4,1,{1,0,0,0},0}},
 {139,{4,1,{1,0,0,0},0}},
 {140,{4,1,{1,0,0,0},0}},
 {141,{4,1,{1,0,0,0},0}},
 {142,{7,4,{1,1,1,1},0}},
 {143,{7,4,{1,1,1,1},0}},
 {144,{7,4,{1,1,1,1},0}},
 {145,{7,4,{1,1,1,1},0}},
 {146,{7,4,{1,1,1,1},0}},
 {147,{7,4,{1,1,1,1},0}},
 {148,{7,4,{1,1,1,1},0}},
 {149,{7,4,{1,1,1,1},0}},
 {150,{7,3,{1,1,1,0},0}},
 {151,{7,3,{1,1,1,0},0}},
 {152,{7,3,{1,1,1,0},0}},
 {153,{7,3,{1,1,1,0},0}},
 {154,{7,3,{1,1,1,0},0}},
 {155,{7,3,{1,1,1,0},0}},
 {156,{7,3,{1,1,1,0},0}},
 {157,{7,3,{1,1,1,0},0}},
 {158,{11,5,{1,1,1,2},0}},
 {159,{11,5,{1,1,1,2},0}},
 {160,{11,5,{1,1,1,2},0}},
 {161,{11,5,{1,1,1,2},0}},
 {162,{11,5,{1,1,1,2},0}},
 {163,{11,5,{1,1,1,2},0}},
 {164,{11,5,{1,1,1,2},0}},
 {165,{11,5,{1,1,1,2},0}},
 {166,{11,5,{1,1,1,2},0}},
 {167,{11,5,{1,1,1,2},0}},
 {168,{11,35,{35,0,0,0},0}},
 {169,{11,21,{21,0,0,0},0}},
 {170,{11,5,{1,1,1,2},0}},
 {171,{11,5,{1,1,1,2},0}},
 {172,{11,5,{1,1,1,2},0}},
 {173,{11,5,{1,1,1,2},0}},
 {174,{11,5,{1,1,1,2},0}},
 {175,{11,5,{1,1,1,2},0}},
 {176,{11,5,{1,1,1,2},0}},
 {177,{11,5,{1,1,1,2},0}},
 {178,{11,14,{14,0,0,0},0}},
 {179,{11,5,{1,1,1,2},0}},
 {180,{11,5,{1,1,1,2},0}},
 {181,{11,5,{1,1,1,2},0}},
 {182,{11,5,{1,1,1,2},0}},
 {183,{11,5,{1,1,1,2},0}},
 {184,{11,5,{1,1,1,2},0}},
 {185,{11,5,{1,1,1,2},0}},
 {186,{7,3,{3,0,0,0},1}},
 {187,{7,3,{1,1,1,0},0}},
 {188,{7,3,{3,0,0,0},0}},
 {189,{7,3,{1,1,1,0},0}},
 {190,{7,3,{3,0,0,0},0}},
 {191,{7,3,{3,0,0,0},0}},
 {192,{7,3,{1,1,1,0},1}},
 {193,{7,3,{1,1,1,0},0}},
 {194,{7,3,{1,1,1,0},0}},
 {195,{7,3,{3,0,0,0},0}},
 {196,{7,3,{1,1,1,0},0}},
 {197,{1,5,{5,0,0,0},1}},
 {198,{1,2,{2,0,0,0},1}},
 {199,{1,5,{5,0,0,0},0}},
 {200,{1,4,{1,3,0,0},0}},
 {201,{1,2,{2,0,0,0},1}},
 {202,{1,4,{1,3,0,0},0}},
 {203,{1,2,{2,0,0,0},1}},
 {204,{11,5,{5,0,0,0},1}},
 {205,{11,5,{5,0,0,0},1}},
 {206,{11,5,{5,0,0,0},0}},
 {207,{1,1,{1,0,0,0},1}},
 {208,{11,1,{1,0,0,0},0}},
 {209,{11,1,{1,0,0,0},0}},
 {210,{7,1,{1,0,0,0},0}},
 {211,{7,3,{1,1,1,0},0}},
 {212,{7,3,{3,0,0,0},0}},
 {213,{7,3,{3,0,0,0},1}},
 {214,{7,3,{3,0,0,0},1}},
 {215,{4,2,{2,0,0,0},0}},
 {216,{4,1,{1,0,0,0},0}},
 {217,{4,2,{2,0,0,0},0}},
 {218,{4,1,{1,0,0,0},1}},
 {219,{4,1,{1,0,0,0},0}},
 {220,{4,1,{1,0,0,0},0}},
 {221,{4,1,{1,0,0,0},0}},
 {222,{4,1,{0,0,0,0},0}},
 {223,{4,1,{0,0,0,0},0}},
 {224,{4,1,{0,0,0,0},0}},
 {226,{4,1,{0,0,0,0},0}},
 {227,{4,1,{0,0,0,0},0}},
 {228,{4,1,{0,0,0,0},0}},
 {229,{4,1,{0,0,0,0},0}},
 {230,{4,1,{0,0,0,0},0}},
 {231,{4,1,{0,0,0,0},0}},
 {232,{4,1,{0,0,0,0},0}},
 {233,{4,1,{0,0,0,0},0}},
 {234,{4,1,{0,0,0,0},0}},
 {235,{4,1,{0,0,0,0},0}},
 {236,{7,3,{1,1,1,0},0}},
 {238,{7,3,{1,1,1,0},0}},
 {239,{7,3,{1,1,1,0},0}},
 {240,{7,3,{1,1,1,0},0}},
 {241,{7,3,{1,1,1,0},0}},
 {242,{7,3,{1,1,1,0},0}},
 {243,{7,3,{1,1,1,0},0}},
 {244,{7,3,{1,1,1,0},0}},
 {245,{7,3,{1,1,1,0},0}},
 {246,{7,3,{1,1,1,0},0}},
 {247,{7,3,{1,1,1,0},0}},
 {248,{7,3,{1,1,1,0},0}},
 {249,{7,3,{1,1,1,0},0}},
 {250,{7,3,{1,1,1,0},0}},
 {251,{7,3,{1,1,1,0},0}},
 {252,{7,3,{1,1,1,0},0}},
 {253,{7,3,{1,1,1,0},0}},
 {254,{7,3,{1,1,1,0},0}},
 {255,{7,3,{1,1,1,0},0}},
 {256,{22,2,{2,0,0,0},1}},
 {257,{22,2,{2,0,0,0},1}},
 {258,{15,1,{1,0,0,0},0}},
 {259,{22,4,{1,1,1,1},0}},
 {260,{15,1,{1,0,0,0},0}},
 {261,{15,1,{1,0,0,0},0}},
 {262,{15,1,{1,0,0,0},0}},
 {263,{15,1,{1,0,0,0},0}},
 {264,{15,1,{1,0,0,0},0}},
 {265,{15,1,{1,0,0,0},0}},
 {266,{15,1,{1,0,0,0},0}},
 {267,{15,1,{1,0,0,0},0}},
 {268,{15,1,{1,0,0,0},0}},
 {269,{15,1,{1,0,0,0},0}},
 {270,{15,1,{1,0,0,0},0}},
 {271,{15,1,{1,0,0,0},0}},
 {272,{15,1,{1,0,0,0},0}},
 {273,{15,1,{1,0,0,0},0}},
 {274,{15,1,{1,0,0,0},0}},
 {275,{15,1,{1,0,0,0},0}},
 {276,{15,1,{1,0,0,0},0}},
 {277,{22,4,{1,1,1,1},0}},
 {278,{22,4,{1,1,1,1},0}},
 {279,{22,2,{1,1,0,0},0}},
 {280,{22,2,{1,1,0,0},0}},
 {281,{15,1,{1,0,0,0},0}},
 {282,{15,1,{1,0,0,0},0}},
 {283,{15,1,{1,0,0,0},0}},
 {284,{22,2,{1,1,0,0},0}},
 {285,{22,2,{1,1,0,0},0}},
 {286,{15,1,{1,0,0,0},0}},
 {287,{15,1,{1,0,0,0},0}},
 {288,{15,1,{1,0,0,0},0}},
 {289,{15,1,{1,0,0,0},0}},
 {290,{15,1,{1,0,0,0},0}},
 {291,{15,1,{1,0,0,0},0}},
 {292,{22,4,{1,1,1,1},0}},
 {293,{22,4,{1,1,1,1},0}},
 {294,{22,4,{1,1,1,1},0}},
 {295,{22,4,{1,1,1,1},0}},
 {296,{22,2,{1,1,0,0},0}},
 {297,{15,1,{1,0,0,0},0}},
 {298,{15,1,{1,0,0,0},0}},
 {299,{15,1,{1,0,0,0},0}},
 {300,{15,1,{1,0,0,0},0}},
 {301,{15,1,{1,0,0,0},0}},
 {302,{15,1,{1,0,0,0},0}},
 {303,{22,2,{1,1,0,0},0}},
 {304,{15,1,{1,0,0,0},0}},
 {305,{15,1,{1,0,0,0},0}},
 {306,{15,1,{1,0,0,0},0}},
 {307,{15,1,{1,0,0,0},0}},
 {308,{15,1,{1,0,0,0},0}},
 {309,{15,1,{1,0,0,0},0}},
 {310,{16,2,{1,1,0,0},0}},
 {311,{16,2,{1,1,0,0},0}},
 {312,{16,2,{1,1,0,0},0}},
 {313,{16,2,{1,1,0,0},0}},
 {314,{16,2,{1,1,0,0},0}},
 {315,{16,2,{1,1,0,0},0}},
 {316,{18,4,{1,1,1,1},0}},
 {317,{18,4,{1,1,1,1},0}},
 {318,{18,4,{1,1,1,1},0}},
 {319,{18,4,{1,1,1,1},0}},
 {320,{18,4,{1,1,1,1},0}},
 {321,{18,4,{1,1,1,1},0}},
 {322,{18,4,{1,1,1,1},0}},
 {323,{18,4,{1,1,1,1},0}},
 {324,{15,1,{1,0,0,0},0}},
 {325,{15,1,{1,0,0,0},0}},
 {326,{16,2,{1,1,0,0},0}},
 {327,{16,2,{1,1,0,0},0}},
 {328,{16,2,{1,1,0,0},0}},
 {329,{16,2,{1,1,0,0},0}},
 {330,{16,2,{1,1,0,0},0}},
 {331,{16,2,{1,1,0,0},0}},
 {332,{16,2,{1,1,0,0},0}},
 {333,{16,2,{1,1,0,0},0}},
 {334,{16,2,{1,1,0,0},0}},
 {335,{22,4,{1,1,1,1},0}},
 {336,{22,4,{1,1,1,1},0}},
 {337,{22,4,{1,1,1,1},0}},
 {338,{22,4,{1,1,1,1},0}},
 {339,{22,4,{1,1,1,1},0}},
 {340,{15,1,{1,0,0,0},0}},
 {341,{15,1,{1,0,0,0},0}},
 {342,{15,1,{1,0,0,0},0}},
 {343,{22,4,{1,1,1,1},0}},
 {344,{16,2,{1,1,0,0},0}},
 {345,{15,1,{1,0,0,0},0}},
 {346,{15,1,{1,0,0,0},0}},
 {347,{16,2,{1,1,0,0},0}},
 {348,{15,1,{1,0,0,0},0}},
 {349,{16,2,{1,1,0,0},0}},
 {350,{16,2,{1,1,0,0},0}},
 {351,{16,2,{1,1,0,0},0}},
 {352,{16,2,{1,1,0,0},0}},
 {353,{16,2,{1,1,0,0},0}},
 {354,{16,2,{1,1,0,0},0}},
 {355,{16,2,{1,1,0,0},0}},
 {356,{15,1,{1,0,0,0},0}},
 {357,{15,1,{1,0,0,0},0}},
 {358,{15,1,{1,0,0,0},0}},
 {359,{15,1,{1,0,0,0},0}},
 {360,{15,1,{1,0,0,0},0}},
 {361,{16,2,{1,1,0,0},0}},
 {362,{15,1,{1,0,0,0},0}},
 {363,{15,1,{1,0,0,0},0}},
 {364,{22,4,{1,1,1,1},0}},
 {365,{15,1,{1,0,0,0},0}},
 {366,{15,1,{1,0,0,0},0}},
 {367,{15,1,{1,0,0,0},0}},
 {368,{15,1,{1,0,0,0},0}},
 {369,{15,1,{1,0,0,0},0}},
 {370,{15,1,{1,0,0,0},0}},
 {371,{15,1,{1,0,0,0},0}},
 {372,{15,1,{1,0,0,0},0}},
 {373,{15,1,{1,0,0,0},0}},
 {374,{18,4,{1,1,1,1},0}},
 {375,{18,4,{1,1,1,1},0}},
 {376,{18,4,{1,1,1,1},0}},
 {377,{18,4,{1,1,1,1},0}},
 {378,{18,4,{1,1,1,1},0}},
 {379,{16,2,{1,1,0,0},0}},
 {380,{16,2,{1,1,0,0},0}},
 {381,{16,2,{1,1,0,0},0}},
 {382,{16,2,{1,1,0,0},0}},
 {383,{16,2,{1,1,0,0},0}},
 {384,{16,2,{1,1,0,0},0}},
 {385,{15,1,{1,0,0,0},0}},
 {386,{22,4,{1,1,1,1},0}},
 {387,{18,4,{1,1,1,1},0}},
 {388,{18,4,{1,1,1,1},0}},
 {389,{18,4,{1,1,1,1},0}},
 {390,{18,4,{1,1,1,1},0}},
 {391,{18,4,{1,1,1,1},0}},
 {392,{18,4,{1,1,1,1},0}},
 {393,{18,4,{1,1,1,1},0}},
 {394,{18,4,{1,1,1,1},0}},
 {395,{18,4,{1,1,1,1},0}},
 {396,{22,4,{1,1,1,1},0}},
 {397,{16,2,{1,1,0,0},0}},
 {398,{15,1,{1,0,0,0},0}},
 {399,{16,2,{1,1,0,0},0}},
 {400,{15,1,{1,0,0,0},0}},
 {401,{16,2,{1,1,0,0},0}},
};
static UInt8 machineInitialized;
static NativeInfo instruction_timing[496];
static char machineDisplay[52];
static UInt8 finalstages[11] = {0,3,4,5,6,10,14,15,17,21,25};
static UInt8 pipeline_units[6][2] = {{1,3},{7,10},{11,14},{16,17},{18,21},{22,25}};
static NativeCompletionBuffers completionbuffers;
static SInt32 fetch_pending, dispatch_available, load_available, scalar_available, vector_available;
static SInt32 loads_issued, scalars_issued, vectors_issued;
static NativeStage pipeline_altivec[26];
static SInt32 scalar_store_busy, load_completed;
static char machineFilename[] = "MachineSimulationAltiVec.c";
extern void CError_Internal(const char *, SInt32);
static void fn_00638800(void);
static int fn_00638a00(NativeInstruction *instruction);
static SInt32 serializes(NativeInstruction *instruction);
static void advance_clock(UInt32 clock);
static void issue(NativeInstruction *instruction);
static int can_issue(NativeInstruction *instruction);
static void initialize(void);
static SInt32 latency(NativeInstruction *instruction);
static void complete_instruction(SInt32 stage);
static void fn_00639410(void);
typedef struct NativeMachine {
 UInt32 header[3];
 SInt32 (*latency)(NativeInstruction *);
 void (*initialize)(void);
 int (*can_issue)(NativeInstruction *);
 void (*issue)(NativeInstruction *);
 void (*advance_clock)(UInt32);
 SInt32 (*serializes)(NativeInstruction *);
 int (*unit_predicate)(NativeInstruction *);
 void (*initialize_timing)(void);
 char *display;
} NativeMachine;
static NativeMachine machineAltiVec = {{6,1,4},latency,initialize,can_issue,issue,advance_clock,serializes,fn_00638a00,fn_00638800,machineDisplay};
typedef char NativeMachineSize[sizeof(NativeMachine)==48?1:-1];

static void fn_00638800(void)
{
 SInt32 i;
 if(!machineInitialized){
  machineInitialized=1;
  for(i=0;i<496;++i)instruction_timing[i]=nativeOpcodeTable[0].info;
  for(i=1;;++i){instruction_timing[nativeOpcodeTable[i].opcode]=nativeOpcodeTable[i].info;if(i==400)break;}
 }
}
static int fn_00638a00(NativeInstruction *instruction)
{
 return instruction_timing[instruction->opcode].unit==16;
}
static SInt32 serializes(NativeInstruction *instruction)
{
 return instruction_timing[instruction->opcode].serializes;
}
static void advance_clock(UInt32 clock)
{
 SInt32 i,j,cycles,adjusted,total,budget,limit,value;
 UInt32 step;
 UInt8 first,last;
 NativeInstruction *instruction;
 for(i=0;i<26;++i){
  if(pipeline_altivec[i].instruction && pipeline_altivec[i].count)--pipeline_altivec[i].count;
 }
 for(i=0;i<3;++i){
  if(!completionbuffers.pending || !completionbuffers.entries[completionbuffers.retireIndex].completed)break;
  completionbuffers.entries[completionbuffers.retireIndex].instruction=0;
  completionbuffers.entries[completionbuffers.retireIndex].completed=0;
  --completionbuffers.pending;++completionbuffers.available;
  completionbuffers.retireIndex=(completionbuffers.retireIndex+1U)&15U;
 }
 load_completed=0;
 for(step=0;step<11;++step){
  j=finalstages[step];
  if(pipeline_altivec[j].instruction && !pipeline_altivec[j].count)complete_instruction(j);
 }
 for(step=0;step<6;++step){
  first=pipeline_units[step][0];last=pipeline_units[step][1];
  while(first<last){
   if(!pipeline_altivec[last].instruction){
    i=last-1;
    instruction=pipeline_altivec[i].instruction;
    if(instruction && !pipeline_altivec[i].count){
     cycles=instruction_timing[instruction->opcode].cycles[last-first];
     adjusted=cycles;
     if((i==11 || (UInt32)(i-12)<=1U) && pipeline_altivec[13].count<0)--adjusted;
     pipeline_altivec[last].instruction=instruction;
     pipeline_altivec[last].count=adjusted;
     pipeline_altivec[i].instruction=0;
     pipeline_altivec[i].count=0;
     if(!cycles)complete_instruction(last);
    }
   }
   --last;
  }
 }
 loads_issued=0;scalars_issued=0;vectors_issued=0;
 budget=12-load_available-scalar_available-vector_available;
 if(budget>3)budget=3;
 if(completionbuffers.available<(UInt32)budget)budget=completionbuffers.available;
 if(fetch_pending<budget)budget=fetch_pending;
 dispatch_available+=budget;fetch_pending-=budget;
 total=load_available+budget;limit=total;if(total>2)limit=2;
 value=dispatch_available;
 if(limit<=dispatch_available){value=total;if(total>2)value=2;}
 load_available=value;
 total=scalar_available+budget;limit=total;if(total>6)limit=6;
 value=dispatch_available;
 if(limit<=dispatch_available){value=total;if(total>6)value=6;}
 scalar_available=value;
 total=vector_available+budget;limit=total;if(total>4)limit=4;
 value=dispatch_available;
 if(limit<=dispatch_available){value=total;if(total>4)value=4;}
 vector_available=value;
 if(load_available+scalar_available+vector_available<dispatch_available)CError_Internal(machineFilename,0x4ca);
 if(fetch_pending<9)fetch_pending+=4;
}
static void issue(NativeInstruction *instruction)
{
 SInt32 cycles,l,s,v;
 UInt32 unit;
 cycles=instruction_timing[instruction->opcode].cycles[0];
 unit=instruction_timing[instruction->opcode].unit;
 fn_00639410();
 if(instruction->opcode==39 || instruction->opcode==54)cycles+=instruction->operandCount-2;
 ++completionbuffers.pending;--completionbuffers.available;
 completionbuffers.entries[completionbuffers.issueIndex].instruction=instruction;
 completionbuffers.entries[completionbuffers.issueIndex].completed=0;
 completionbuffers.issueIndex=(completionbuffers.issueIndex+1U)&15U;
 --dispatch_available;
 if(dispatch_available<0)CError_Internal(machineFilename,0x400);
 if(unit==11){--load_available;++loads_issued;}
 else if(unit>=15 && unit<=22){--vector_available;++vectors_issued;}
 else if(unit){--scalar_available;++scalars_issued;}
 l=dispatch_available;if(load_available<=dispatch_available)l=load_available;
 s=dispatch_available;if(scalar_available<=dispatch_available)s=scalar_available;
 v=dispatch_available;if(vector_available<=dispatch_available)v=vector_available;
 load_available=l;scalar_available=s;vector_available=v;
 if(unit==7 && instruction && (instruction->flags&4) && !instruction->operandKind && instruction->operandClass==3)scalar_store_busy=1;
 if(unit==4){
  if(!pipeline_altivec[4].instruction)unit=4;
  else if(!pipeline_altivec[5].instruction)unit=5;
  else if(!pipeline_altivec[6].instruction)unit=6;
  if(instruction->recordFlags&0x100000){
   switch(instruction->opcode){case 97:case 100:case 101:case 103:case 104:case 105:case 106:case 107:case 108:case 109:++cycles;}
  }
 }
 pipeline_altivec[unit].instruction=instruction;
 pipeline_altivec[unit].count=cycles;
}
static int can_issue(NativeInstruction *instruction)
{
 SInt32 unit;
 UInt8 stage;
 SInt32 busy;
 if(!completionbuffers.available)return 0;
 unit=instruction_timing[instruction->opcode].unit;
 if(unit==4){if(pipeline_altivec[4].instruction && pipeline_altivec[5].instruction)return 0;}
 else if(pipeline_altivec[unit].instruction)return 0;
 if(unit==11){
  busy=0;stage=14;
  do{if(pipeline_altivec[stage].instruction)++busy;--stage;}while(stage>=11);
  if(busy>=3 && load_completed)return 0;
 }
 if(unit==7 && scalar_store_busy && instruction && (instruction->flags&4) && !instruction->operandKind && instruction->operandClass==3)return 0;
 if(dispatch_available<=0)return 0;
 if(unit==11){if(load_available<1 || loads_issued>=1)return 0;}
 else if(unit>=15 && unit<=22){if(vector_available<1 || vectors_issued>=2)return 0;}
 else if(unit && (scalar_available<1 || scalars_issued>=3))return 0;
 if(pipeline_altivec[7].instruction && pipeline_altivec[7].count>1 && (pipeline_altivec[7].instruction->opcode==39 || pipeline_altivec[7].instruction->opcode==54))return 0;
 return 1;
}
static void initialize(void)
{
 SInt32 i;
 scalar_store_busy=0;load_completed=0;
 fetch_pending=4;dispatch_available=3;load_available=2;scalar_available=3;vector_available=2;
 loads_issued=0;scalars_issued=0;vectors_issued=0;
 for(i=0;i<26;++i)pipeline_altivec[i].instruction=0;
 completionbuffers.available=16;completionbuffers.pending=0;completionbuffers.retireIndex=0;completionbuffers.issueIndex=0;
 for(i=0;i<16;++i){completionbuffers.entries[i].instruction=0;completionbuffers.entries[i].completed=0;}
 fn_00639410();
}
static SInt32 latency(NativeInstruction *instruction)
{
 SInt32 result;
 result=instruction_timing[instruction->opcode].latency;
 if(instruction->recordFlags&0x100000){
  switch(instruction->opcode){case 97:case 100:case 101:case 103:case 104:case 105:case 106:case 107:case 108:case 109:++result;}
 }
 if(instruction->opcode==39 || instruction->opcode==54)result+=instruction->operandCount-2;
 return result;
}
static void complete_instruction(SInt32 stage)
{
 NativeInstruction *instruction;
 SInt32 i;
 instruction=pipeline_altivec[stage].instruction;
 if(stage==14 && instruction)load_completed=1;
 if(instruction && (instruction->flags&4) && !instruction->operandKind && instruction->operandClass==3)scalar_store_busy=0;
 for(i=0;i<16 && completionbuffers.entries[i].instruction!=instruction;++i){}
 completionbuffers.entries[i].completed=1;
 pipeline_altivec[stage].instruction=0;
}
static void fn_00639410(void)
{
 SInt32 i;
 UInt32 head=completionbuffers.issueIndex;
 char value;
 for(i=0;i<16;++i){
  machineDisplay[i*3]=' ';
  value=' ';
  if(completionbuffers.entries[i].instruction)value='|';
  else if(i==head)value='+';
  machineDisplay[i*3+1]=value;machineDisplay[i*3+2]=value;
 }
 machineDisplay[48]='|';machineDisplay[49]=head+'A';machineDisplay[50]=':';machineDisplay[51]=0;
}
