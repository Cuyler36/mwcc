#include <string.h>
#pragma pack(push, 2)
typedef struct PCodeInstruction PCodeInstruction;
typedef struct PCodeBlock PCodeBlock;
typedef struct PCodeLabel PCodeLabel;
typedef struct PCodeEdge PCodeEdge;
typedef struct PCodeOperand {
    unsigned char kind, registerClass;
    unsigned short flags;
    union { short reg; int immediate; void *pointer; } value;
    unsigned char unknown08[6];
} PCodeOperand;
typedef struct PCodeSource { void *location; } PCodeSource;
typedef struct PCodeHeader {
    PCodeInstruction *next, *previous;
    PCodeBlock *block;
    unsigned int flags, flags2;
    unsigned char unknown14[12];
    PCodeSource *source;
    unsigned int offset;
    short opcode, operandCount;
} PCodeHeader;
struct PCodeInstruction {
    PCodeInstruction *next, *previous;
    PCodeBlock *block;
    unsigned int flags, flags2;
    unsigned char unknown14[12];
    PCodeSource *source;
    unsigned int offset;
    short opcode, operandCount;
    PCodeOperand operands[1];
};
struct PCodeBlock {
    PCodeBlock *next, *previous;
    PCodeLabel *labels;
    PCodeEdge *predecessors, *successors;
    PCodeInstruction *first, *last;
    int number, offset, version;
    short instructionCount;
    unsigned short flags;
    short unknown2c;
};
struct PCodeLabel {
    PCodeLabel *next;
    void *destination;
    short resolved;
    unsigned short number;
};
struct PCodeEdge {
    PCodeEdge *nextHash, *nextSuccessor, *nextPredecessor;
    PCodeBlock *from, *to;
    int number;
    unsigned short hash, flags;
};
typedef struct PCodePendingBranch {
    struct PCodePendingBranch *next;
    PCodeBlock *block;
    unsigned short flags;
} PCodePendingBranch;
#pragma pack(pop)
extern PCodeBlock *pcbasicblocks, *pclastblock;
extern PCodeSource *pcodeCurrentSource;
extern void *gCurrentStatement;
extern int pcblockcount, pcloopweight;
extern unsigned short pclabelcount;
extern PCodeEdge *pcodeEdgeHash[1997];
extern int pcodeEdgeCount;
extern PCodeInstruction *vformatpcode(short, char *);
extern void *lalloc(int);
extern void memclrw(void *, int);
extern void CError_Internal(const char *, int);
extern void fn_005a0930(void);
extern void computedepthfirstordering(void);
extern void *galloc(int);
extern PCodeBlock **depthfirstordering;
extern int depthfirstorder;
extern PCodeBlock *epilogue;
extern PCodeOperand *fn_0058aec0(PCodeInstruction *);
PCodeEdge *fn_005821e0(PCodeBlock *, PCodeBlock *);
void fn_00582100(PCodeBlock *, PCodeBlock *);
PCodeLabel *makepclabel(void);
void pclabel(PCodeBlock *, PCodeLabel *);
void deletepcode(PCodeInstruction *);
void appendpcode(PCodeBlock *, PCodeInstruction *);

void computedepthfirstordering(void)
{
    typedef struct Frame { PCodeBlock *block; PCodeEdge *edge; } Frame;
    PCodeBlock *block;
    Frame *stack;
    int count;
    depthfirstordering = lalloc(pcblockcount * 4);
    memclrw(depthfirstordering, pcblockcount * 4);
    depthfirstorder = pcblockcount;
    for (block = pcbasicblocks; block; block = block->next) block->flags &= ~4;
    stack = galloc(pcblockcount * 8);
    pcbasicblocks->flags |= 4;
    stack[0].block = pcbasicblocks;
    stack[0].edge = pcbasicblocks->successors;
    count = 1;
    while (count) {
        PCodeEdge *edge = stack[count - 1].edge;
        if (edge) {
            stack[count - 1].edge = edge->nextSuccessor;
            block = edge->to;
            if (!(block->flags & 4)) {
                block->flags |= 4;
                stack[count].block = block;
                stack[count].edge = block->successors;
                ++count;
            }
        } else {
            --count;
            depthfirstordering[--depthfirstorder] = stack[count].block;
        }
    }
    while (depthfirstorder) depthfirstordering[--depthfirstorder] = 0;
}

unsigned char fn_005824a0(PCodeBlock *first, PCodeBlock *second)
{
    PCodeInstruction *last;
    PCodeOperand *operand;
    PCodeLabel *label;
    if (first->next != second || !first->successors || first->successors->nextSuccessor ||
        !second->predecessors || second->predecessors->nextPredecessor || first->successors->to != second)
        return 0;
    last = first->last;
    if (!last) return 1;
    if (last->flags & 8) return 0;
    if (last->flags & 0x180) return 0;
    if ((*(unsigned long long *)&last->flags & 0x181ULL) != 1) return 1;
    operand = fn_0058aec0(last);
    if (!operand || operand->kind != 6) return 0;
    label = *(PCodeLabel **)((char *)operand + 2);
    return label && label->destination == second;
}

void fn_005822a0(PCodeBlock *first, PCodeBlock *second)
{
    PCodeInstruction *instruction, *next;
    PCodeEdge *edge;
    if (!fn_005824a0(first, second)) CError_Internal("PCode.c", 931);
    instruction = first->last;
    if (instruction && (*(unsigned long long *)&instruction->flags & 0x181ULL) == 1) {
        PCodeOperand *operand = fn_0058aec0(instruction);
        if (operand && operand->kind == 6) {
            PCodeLabel *label = *(PCodeLabel **)((char *)operand + 2);
            if (label && label->destination == second) deletepcode(instruction);
            else CError_Internal("PCode.c", 942);
        } else instruction->flags |= 0x100;
    }
    for (instruction = second->first; instruction; instruction = next) {
        next = instruction->next;
        deletepcode(instruction);
        appendpcode(first, instruction);
        if (second == epilogue) first->last->flags |= 0x80;
    }
    if (second == epilogue) return;
    for (edge = second->successors; edge; edge = edge->nextSuccessor) {
        PCodeBlock *to = edge->to;
        fn_005821e0(first, to);
        fn_00582100(second, to);
    }
    fn_00582100(first, second);
    if (second->previous) second->previous->next = second->next;
    else pcbasicblocks = second->next;
    if (second->next) second->next->previous = second->previous;
    else pclastblock = second->previous;
    second->flags |= 0x20;
}

PCodeBlock *fn_00582560(PCodeBlock *before)
{
    PCodeBlock *block = lalloc(46);
    memclrw(block, 46);
    block->number = pcblockcount++;
    block->version = before->version;
    pclabel(block, makepclabel());
    block->next = before;
    block->previous = before->previous;
    before->previous->next = block;
    before->previous = block;
    return block;
}

PCodeBlock *fn_00582610(PCodeBlock *first, PCodeBlock *second)
{
    PCodeBlock *block;
    if (first->next != second) CError_Internal("PCode.c", 700);
    block = lalloc(46);
    memclrw(block, 46);
    block->number = pcblockcount++;
    block->version = first->version;
    pclabel(block, makepclabel());
    first->next = block;
    block->previous = first;
    block->next = second;
    second->previous = block;
    fn_00582100(first, second);
    fn_005821e0(first, block);
    fn_005821e0(block, second);
    return block;
}

void fn_00582100(PCodeBlock *from, PCodeBlock *to)
{
    PCodeEdge *edge;
    PCodeEdge **link;
    int hash = ((from->number << 8) ^ to->number) % 1997;
    for (edge = pcodeEdgeHash[hash]; edge; edge = edge->nextHash)
        if (edge->from == from && edge->to == to) break;
    if (!edge) CError_Internal("PCode.c", 1060);
    for (link = &to->predecessors; *link != edge; link = &(*link)->nextPredecessor) {}
    *link = edge->nextPredecessor;
    for (link = &from->successors; *link != edge; link = &(*link)->nextSuccessor) {}
    *link = edge->nextSuccessor;
    for (link = &pcodeEdgeHash[edge->hash]; *link != edge; link = &(*link)->nextHash) {}
    *link = edge->nextHash;
}

void deleteunreachableblocks(void)
{
    PCodeBlock *block;
    computedepthfirstordering();
    for (block = pcbasicblocks->next; block; block = block->next) {
        if (!(block->flags & 4) && !(block->flags & 0x190)) {
            if (block->previous) block->previous->next = block->next;
            else pcbasicblocks = block->next;
            if (block->next) block->next->previous = block->previous;
            else pclastblock = block->previous;
            block->flags |= 0x20;
        }
    }
}

void initpcode(void)
{
    int i;
    for (i = 0; i < 1997; ++i) pcodeEdgeHash[i] = 0;
    pcbasicblocks = pclastblock = 0;
    pclabelcount = pcblockcount = pcodeEdgeCount = 0;
    pcloopweight = 1;
    pcodeCurrentSource = 0;
    fn_005a0930();
}

static inline PCodeSource *current_source(void)
{
    PCodeSource *source = pcodeCurrentSource;
    if (source && source->location) return source;
    return 0;
}

static inline void inherit_source(PCodeInstruction *instruction)
{
    if (!instruction->source) {
        if (gCurrentStatement) instruction->source = current_source();
        else instruction->source = 0;
    }
}

void appendpcode(PCodeBlock *block, PCodeInstruction *instruction)
{
    if (block->first) {
        instruction->next = 0;
        instruction->previous = block->last;
        block->last->next = instruction;
        block->last = instruction;
    } else {
        block->first = block->last = instruction;
        instruction->next = instruction->previous = 0;
    }
    instruction->block = block;
    block->instructionCount++;
}

PCodeInstruction *emitpcode(short opcode, ...)
{
    char *arguments = (char *)((int)&opcode + (((int)(&opcode + 1) - (int)&opcode + 3) / 4) * 4);
    PCodeInstruction *instruction = vformatpcode(opcode, arguments);
    inherit_source(instruction);
    appendpcode(pclastblock, instruction);
    return instruction;
}

PCodeInstruction *makepcode(short opcode, ...)
{
    char *arguments = (char *)((int)&opcode + (((int)(&opcode + 1) - (int)&opcode + 3) / 4) * 4);
    PCodeInstruction *instruction = vformatpcode(opcode, arguments);
    inherit_source(instruction);
    return instruction;
}

PCodeInstruction *copypcode(PCodeInstruction *original)
{
    int extra = 0, index;
    PCodeInstruction *copy;
    if ((original->flags2 & 0x20000) && !(original->flags2 & 0x100000)) extra++;
    if (original->operandCount + extra < 6) extra = 6 - original->operandCount;
    copy = lalloc(44 + (original->operandCount + extra) * 14);
    memclrw(copy, 44 + (original->operandCount + extra) * 14);
    *(PCodeHeader *)copy = *(PCodeHeader *)original;
    for (index = 0; index < original->operandCount; index++) copy->operands[index] = original->operands[index];
    while (extra) {
        copy->operands[original->operandCount + extra - 1].kind = 8;
        extra--;
    }
    return copy;
}

PCodeLabel *makepclabel(void)
{
    PCodeLabel *label = lalloc(12);
    memclrw(label, 12);
    label->number = pclabelcount++;
    return label;
}

PCodeBlock *makepcblock(void)
{
    PCodeBlock *block = lalloc(46);
    memclrw(block, 46);
    block->version = pcloopweight;
    block->number = pcblockcount++;
    if (pclastblock) {
        pclastblock->next = block;
        block->previous = pclastblock;
    } else pcbasicblocks = block;
    pclastblock = block;
    return block;
}

void deletepcode(PCodeInstruction *instruction)
{
    PCodeBlock *block = instruction->block;
    if (instruction->previous) instruction->previous->next = instruction->next;
    else block->first = instruction->next;
    if (instruction->next) instruction->next->previous = instruction->previous;
    else block->last = instruction->previous;
    instruction->block = 0;
    block->instructionCount--;
    block->flags &= ~8;
}

void insertpcodebefore(PCodeInstruction *before, PCodeInstruction *instruction)
{
    PCodeBlock *block = before->block;
    if (before->previous) before->previous->next = instruction;
    else block->first = instruction;
    instruction->next = before;
    instruction->previous = before->previous;
    before->previous = instruction;
    inherit_source(instruction);
    if (!instruction->source || !instruction->source->location) instruction->source = before->source;
    instruction->block = block;
    block->instructionCount++;
    block->flags &= ~8;
}

void insertpcodeafter(PCodeInstruction *after, PCodeInstruction *instruction)
{
    PCodeBlock *block = after->block;
    if (after->next) after->next->previous = instruction;
    else block->last = instruction;
    instruction->previous = after;
    instruction->next = after->next;
    after->next = instruction;
    inherit_source(instruction);
    if (!instruction->source || !instruction->source->location) instruction->source = after->source;
    instruction->block = block;
    block->instructionCount++;
    block->flags &= ~8;
}

int pccomputeoffsets(void)
{
    PCodeBlock *block;
    PCodeInstruction *instruction;
    int offset = 0;
    for (block = pcbasicblocks; block; block = block->next) {
        block->offset = offset;
        for (instruction = block->first; instruction; instruction = instruction->next) {
            instruction->offset = offset;
            offset += 4;
        }
    }
    return offset;
}

void setpcodeflags(unsigned long long flags)
{
    PCodeInstruction *instruction = pclastblock->last;
    *(unsigned long long *)&instruction->flags |= flags;
    if (flags & 0x100) pclastblock->last->flags &= ~0x6010;
}

void fn_005820e0(PCodeSource *source)
{
    pcodeCurrentSource = source && source->location ? source : 0;
}

PCodeEdge *fn_005821e0(PCodeBlock *from, PCodeBlock *to)
{
    int hash = ((from->number << 8) ^ to->number) % 1997;
    PCodeEdge *edge;
    for (edge = pcodeEdgeHash[hash]; edge; edge = edge->nextHash)
        if (edge->from == from && edge->to == to) return edge;
    edge = lalloc(28);
    memclrw(edge, 28);
    edge->from = from;
    edge->to = to;
    edge->number = pcodeEdgeCount++;
    edge->hash = hash;
    edge->nextHash = pcodeEdgeHash[hash];
    pcodeEdgeHash[hash] = edge;
    edge->nextSuccessor = from->successors;
    from->successors = edge;
    edge->nextPredecessor = to->predecessors;
    to->predecessors = edge;
    return edge;
}

void pcbranch(PCodeBlock *block, PCodeLabel *label, unsigned short flags)
{
    PCodePendingBranch *pending;
    if (label->resolved) fn_005821e0(block, label->destination)->flags |= flags;
    else {
        pending = lalloc(10);
        memclrw(pending, 10);
        pending->block = block;
        pending->flags = flags;
        pending->next = label->destination;
        label->destination = pending;
    }
}

void pclabel(PCodeBlock *block, PCodeLabel *label)
{
    PCodePendingBranch *pending = label->destination;
    while (pending) {
        fn_005821e0(pending->block, block)->flags |= pending->flags;
        pending = pending->next;
    }
    label->destination = block;
    label->resolved = 1;
    label->next = block->labels;
    block->labels = label;
}

void fn_00582b90(PCodeLabel *label)
{
    if (pclastblock->instructionCount) {
        pcbranch(pclastblock, label, 0);
        makepcblock();
    }
    pclabel(pclastblock, label);
}

void fn_00582b50(void)
{
    fn_00582b90(makepclabel());
}

void fn_00582910(PCodeBlock *block, PCodeInstruction *instruction)
{
    PCodeInstruction *first = block->first;
    if (first) insertpcodebefore(first, instruction);
    else appendpcode(block, instruction);
}
