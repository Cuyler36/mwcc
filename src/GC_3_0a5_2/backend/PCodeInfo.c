#pragma pack(push, 2)
typedef unsigned long long PCodeFlags;
typedef struct PCodeOperand {
    /* Register operands use +4; immediate/label payloads use +2,
     * and memory operands carry an additional object pointer at +6. */
    unsigned char kind, registerClass;
    unsigned short flags;
    union { short reg; int immediate; void *pointer; } value;
    unsigned char unknown08[6];
} PCodeOperand;
typedef struct PCodeInstruction {
    void *next, *previous, *block;
    PCodeFlags flags;
    unsigned char unknown14[12];
    void *source;
    unsigned int offset;
    short opcode, operandCount;
    PCodeOperand operands[1];
} PCodeInstruction;
typedef struct PCodeDescriptor {
    const char *name, *format;
    unsigned char operandCount, unknown09;
    PCodeFlags flags;
    unsigned int encoding;
} PCodeDescriptor;
#pragma pack(pop)
typedef char PCodeOperandSizeCheck[sizeof(PCodeOperand) == 14 ? 1 : -1];
typedef char PCodeDescriptorSizeCheck[sizeof(PCodeDescriptor) == 22 ? 1 : -1];

extern PCodeDescriptor pcodeInfoDescriptors[];
extern PCodeInstruction *makepcode(short, ...);
extern void pcsetrecordbit(PCodeInstruction *);
extern void CError_Internal(const char *, int);
extern int fn_00587410(void *);
extern char pcodeNameBuffer[40];
extern int fn_00407fd0(char *, unsigned int, const char *, ...);
extern int first_temporary_register, last_temporary_register;
extern short pcodeSpecialBaseRegister;
extern signed char fn_00579560(void *);
extern unsigned char pcodeFloatOption;
extern short pcodeProcessor;
PCodeInstruction *makecopyinstruction(PCodeOperand *, PCodeOperand *);
extern void insertpcodebefore(PCodeInstruction *, PCodeInstruction *);
extern void deletepcode(PCodeInstruction *);
extern void *fn_00403ff0(int);
extern int fn_0042d960(const char *);
extern void *lalloc(int);
extern void memclrw(void *, int);
extern void pcsetsideeffects(PCodeInstruction *);
extern unsigned char pcodeHasExtendedRegisters, pcodeHasProcessorRegisters;
extern short pcodeSpecialRegisters[4];
extern unsigned char fn_00453150(void *), fn_00587320(void *), fn_00587380(void *);
extern unsigned char fn_004c3f60(void *), fn_00581be0(void *);
extern void *fn_005a05d0(void *, int, int);
extern char *fn_004041a0(const char *, int);
static inline int pcode_name_character(int);
int pcode_const_from_format(const char *, int *);
int pcode_check_imm_bits(int, int, char);
int nbytes_loaded_or_stored_by(PCodeInstruction *);

static inline int pcode_name_character(int c)
{
    if (c >= 0 && c < 256) {
        char *runtime = fn_00403ff0(1);
        char *locale = *(char **)(runtime + 444);
        return (*(unsigned short **)(locale + 8))[c] & 8;
    }
    return 0;
}

int pcode_const_from_format(const char *format, int *value)
{
    char name[32];
    int count;
    for (count = 0; count < 30 && format[count] && pcode_name_character((signed char)format[count]); ++count)
        name[count] = format[count];
    name[count] = 0;
    *value = fn_0042d960(name);
    return count;
}

void pcode_get_hi_lo(int bits, char kind, int *maximum, int *minimum)
{
    if (bits == 0) *maximum = *minimum = 0;
    else if (bits == 32) { *maximum = 0x7fffffff; *minimum = 0x80000000; }
    else if (bits > 0 && bits < 32) {
        switch (kind) {
        case 'U': *maximum = 1 << bits; *minimum = 1; break;
        case 'K': case 'k': case 'u': *maximum = (1 << bits) - 1; *minimum = 0; break;
        case 'i': case 'x': *maximum = (1 << bits) - 1; *minimum = -(1 << (bits - 1)); break;
        default: *maximum = (1 << (bits - 1)) - 1; *minimum = -(1 << (bits - 1));
        }
    } else CError_Internal("PCodeInfo.c", 189);
}

int pcode_check_imm_bits(int value, int bits, char kind)
{
    int alignment = 0;
    int maximum, minimum;
    if (bits >= 0 && bits < 32) {
        if (!bits) maximum = minimum = 0;
        else {
            switch (kind) {
            case 'U': maximum = 1 << bits; minimum = 1; break;
            case 'u': maximum = (1 << bits) - 1; minimum = 0; break;
            case 'i': case 'x': maximum = (1 << bits) - 1; minimum = -(1 << (bits - 1)); break;
            default:
                if (kind >= '1' && kind <= '4') {
                    char name[2];
                    name[0] = kind;
                    name[1] = 0;
                    alignment = fn_0042d960(name);
                }
                maximum = (1 << (bits - 1)) - 1;
                minimum = -(1 << (bits - 1));
            }
        }
        if (value < minimum || value > maximum) return 1;
        if (alignment > 0 && value != ((value >> alignment) << alignment)) return 1;
    } else if (bits > 32) CError_Internal("PCodeInfo.c", 243);
    return 0;
}

static inline unsigned int pcode_object_qualifiers(char *object)
{
    char *type = *(char **)(object + 16);
    return (*type == 12 || *type == 13) ? *(unsigned int *)(type + 10) : *(unsigned int *)(object + 20);
}

#define PCODE_ARG(type) (*(type *)((arguments += 4) - 4))
#define PCODE_VALUE(operand) (*(int *)((char *)(operand) + 2))
#define PCODE_OBJECT(operand) (*(void **)((char *)(operand) + 6))

PCodeInstruction *vformatpcode(short opcode, char *arguments)
{
    PCodeDescriptor *descriptor = &pcodeInfoDescriptors[opcode];
    const char *format = descriptor->format;
    int count = descriptor->operandCount;
    unsigned int variableCount = 0;
    int extra = 0;
    PCodeInstruction *instruction;
    PCodeOperand *operand, *end;
    if (*format == '#') {
        variableCount += PCODE_ARG(int);
        count += variableCount;
        ++format;
    }
    if (descriptor->flags & 0x2000000000000ULL) ++extra;
    if (count + extra < 6) extra = 6 - count;
    instruction = lalloc(44 + (count + extra) * 14);
    memclrw(instruction, 44 + (count + extra) * 14);
    instruction->opcode = opcode;
    instruction->operandCount = count;
    instruction->flags = descriptor->flags;
    operand = instruction->operands;
    end = operand + instruction->operandCount;
    while (*format) {
        int mode = 1, reg = -1;
        char kind;
        if (operand >= end) CError_Internal("PCodeInfo.c", 325);
        if (*format == ',' || *format == ';') ++format;
        if (*format == '[' || *format == '(') ++format;
        if (*format == '=') { mode = 2; ++format; }
        else if (*format == '+') { mode = 3; ++format; }
        if (*format == '^') { mode |= 0x8000; ++format; pcodeHasExtendedRegisters = 1; }
        else if (*format == ':') { mode |= 0xc000; ++format; pcodeHasExtendedRegisters = 1; }
        else if (*format == '.') { mode |= 0x4000; ++format; }
        else if (*format == '`') {
            if (pcodeProcessor == 0x16) { mode |= 0x2000; pcodeHasProcessorRegisters = 1; }
            ++format;
        }
        if (*format == '-') ++format;
        if (*format == '?') ++format;
        if (*format == '!') ++format;
        if (*format == '$') {
            ++format;
            format += pcode_const_from_format(format + 1, &reg);
        }
        kind = *format;
        switch (kind) {
        case 'b':
            if (reg == -1) reg = PCODE_ARG(int);
            if (!reg) mode = 0;
            operand->kind = 0; operand->registerClass = 4; operand->value.reg = reg; operand->flags = mode;
            break;
        case 'r': case 'f': case 'v': case 'z': case 'c':
            if (kind == 'z' && operand->value.reg > 3 && operand->value.reg <= 7)
                CError_Internal("PCodeInfo.c", 432);
            if (reg == -1) reg = PCODE_ARG(int);
            operand->kind = 0;
            operand->registerClass = kind == 'r' ? 4 : kind == 'f' ? 3 : kind == 'v' ? 2 : 1;
            operand->value.reg = reg; operand->flags = mode;
            break;
        case 'C': case 'L': case 'X':
            operand->kind = 0; operand->registerClass = 0;
            operand->value.reg = kind == 'C' ? 2 : kind == 'L' ? 1 : 0; operand->flags = mode;
            break;
        case 'V': {
            unsigned int index = variableCount;
            while (index--) {
                operand->kind = 0; operand->registerClass = 4;
                operand->value.reg = 31 - index; operand->flags = mode;
                ++operand;
            }
            --operand;
            break;
        }
        case 'Y': {
            int index;
            if (instruction->opcode == 0x7a) {
                int mask = PCODE_VALUE(instruction->operands);
                for (index = 0; index < 8; ++index) {
                    if ((0x80 >> index) & mask) {
                        operand->kind = 0; operand->registerClass = 1;
                        operand->value.reg = index; operand->flags = 2;
                        ++operand;
                    }
                }
            } else {
                for (index = 0; index < 8; ++index) {
                    operand->kind = 0; operand->registerClass = 1;
                    operand->value.reg = index; operand->flags = 1;
                    ++operand;
                }
            }
            --operand;
            break;
        }
        case 'Z':
            operand->kind = 0; operand->registerClass = 1; operand->value.reg = 0; operand->flags = mode;
            break;
        case 'P': case 's': case 'S': {
            int found = -1, index;
            if (kind == 'P' || kind == 'S') {
                if (!format[1] || !pcode_name_character((signed char)format[1]))
                    CError_Internal("PCodeInfo.c", kind == 'P' ? 488 : 539);
                if (kind == 'S') reg = -1;
                if (kind == 'P') {
                    int ignored;
                    format += pcode_const_from_format(format + 1, &ignored);
                } else format += pcode_const_from_format(format + 1, &reg);
            }
            if (reg == -1 && kind != 'S') reg = PCODE_ARG(int);
            for (index = 0; index < 4; ++index) {
                if (reg == pcodeSpecialRegisters[index]) {
                    operand->kind = 0; operand->registerClass = 0;
                    operand->value.reg = index; operand->flags = mode;
                    found = index;
                    if ((mode & 2) && reg == 0x100) pcsetsideeffects(instruction);
                    break;
                }
            }
            if (found < 0) {
                pcsetsideeffects(instruction);
                operand->kind = 1; operand->registerClass = 0;
                operand->value.reg = reg; operand->flags = mode;
            }
            break;
        }
        case 'T':
            if (reg == -1) reg = PCODE_ARG(int);
            if (reg == 0x10c || reg == 0x10d) {
                operand->kind = 0; operand->registerClass = 0;
                operand->value.reg = reg == 0x10c ? 0x11c : 0x11d; operand->flags = mode;
            } else CError_Internal("PCodeInfo.c", 525);
            break;
        case '%': {
            int constant, baseMode, base;
            ++format;
            format += pcode_const_from_format(format + 1, &constant);
            if (format[1] == '(') {
                ++format;
                baseMode = 1;
                if (format[1] == '=') { ++format; baseMode = 2; }
                else if (format[1] == '+') { ++format; baseMode = 3; }
                base = -1;
                if (format[1] == '$') {
                    ++format;
                    format += pcode_const_from_format(format + 1, &base);
                }
                if (format[1] == 'b') {
                    if (base == -1) base = PCODE_ARG(int);
                    if (!base) baseMode = 0;
                } else CError_Internal("PCodeInfo.c", 603);
                operand->kind = 0; operand->registerClass = 4;
                operand->value.reg = base; operand->flags = baseMode;
                ++operand;
            }
            operand->kind = 2; PCODE_VALUE(operand) = constant;
            break;
        }
        case 'o': kind = 'x';
        case 'a': case 'i': case 'k': case 'K': case 'n': case 'u': case 'U': case 'w': case 'x': {
            int bits = 16;
            if (kind == 'a') {
                if (!format[1] || !pcode_name_character((signed char)format[1]))
                    CError_Internal("PCodeInfo.c", 633);
                kind = *++format;
            } else if (kind == 'k' || kind == 'K') bits = 32;
            if (format[1] && pcode_name_character((signed char)format[1]))
                format += pcode_const_from_format(format + 1, &bits);
            operand->kind = 2; PCODE_VALUE(operand) = PCODE_ARG(int);
            if (pcode_check_imm_bits(PCODE_VALUE(operand), bits, kind)) CError_Internal("PCodeInfo.c", 646);
            break;
        }
        case 'Q': case 'q':
            if (reg == -1) reg = PCODE_ARG(int);
            operand->kind = 0; operand->registerClass = 1; operand->value.reg = reg; operand->flags = mode;
            ++operand;
        case 'B': case 'N': case 'D': case 'R': case 't': {
            int bits = kind == 'N' ? 6 : kind == 'D' || kind == 'R' ? 10 : kind == 't' ? 5 : 4;
            operand->kind = 2; PCODE_VALUE(operand) = PCODE_ARG(int);
            if (pcode_check_imm_bits(PCODE_VALUE(operand), bits, 'u'))
                CError_Internal("PCodeInfo.c", kind == 'N' ? 677 : kind == 'D' || kind == 'R' ? 686 : kind == 't' ? 694 : 712);
            break;
        }
        case 'l': {
            void *label = PCODE_ARG(void *);
            if (label) { operand->kind = 6; PCODE_VALUE(operand) = (int)label; }
            else {
                char *object = PCODE_ARG(char *);
                operand->kind = 4;
                if (*object != 5) CError_Internal("PCodeInfo.c", 725);
                PCODE_OBJECT(operand) = object; PCODE_VALUE(operand) = 0; operand->registerClass = 4;
            }
            break;
        }
        case 'd': case 'h': {
            int baseMode = 1;
            if (format[1] != '(') CError_Internal("PCodeInfo.c", 738);
            format += 2;
            if (*format == '=') { ++format; baseMode = 2; }
            else if (*format == '+') { ++format; baseMode = 3; }
            if (*format != 'b') CError_Internal("PCodeInfo.c", 764);
            if (reg == -1) reg = PCODE_ARG(int);
            if (!reg) baseMode = 0;
            operand->kind = 0; operand->registerClass = 4; operand->value.reg = reg; operand->flags = baseMode;
            ++operand;
        }
        case 'm': case 'M': {
            char *object = PCODE_ARG(char *);
            if (object) {
                if (*object != 5) CError_Internal("PCodeInfo.c", kind == 'M' ? 857 : 782);
                if (object[2] == 2) {
                    int value = PCODE_ARG(int) + *(int *)(object + 64);
                    operand->kind = 2;
                    PCODE_VALUE(operand) = kind == 'M' ? value : (short)value;
                } else {
                    operand->kind = 4; PCODE_OBJECT(operand) = object; PCODE_VALUE(operand) = PCODE_ARG(int);
                    if (kind != 'M') {
                        if (instruction->flags & 0x60006) {
                            *(void **)((char *)instruction + 28) = fn_005a05d0(object, PCODE_VALUE(operand), nbytes_loaded_or_stored_by(instruction));
                            if (fn_00453150(object)) instruction->flags |= 0x80;
                            if (pcode_object_qualifiers(object) & 1) instruction->flags |= 0x40;
                        } else if (instruction->opcode == 0x3f) {
                            *(void **)((char *)instruction + 28) = fn_005a05d0(object, PCODE_VALUE(operand), 1);
                        }
                    }
                    if (instruction->flags & 6) {
                        if (pcode_object_qualifiers(object) & 2) instruction->flags |= 0x80;
                        if (pcode_object_qualifiers(object) & 1) instruction->flags |= 0x40;
                    }
                    if (kind == 'M') operand->registerClass = object[2] == 1 ? 12 : 8;
                    else if (instruction->flags & 9) operand->registerClass = 4;
                    else if (object[2] == 1) {
                        if (instruction->flags & 0x80000000000ULL) {
                            if (((instruction->opcode >= 0x192 && instruction->opcode <= 0x193) ||
                                (instruction->opcode >= 0x196 && instruction->opcode <= 0x197)) && fn_00587320(object))
                                operand->registerClass = 15;
                            else { CError_Internal("PCodeInfo.c", 155); operand->registerClass = 0; }
                        } else operand->registerClass = fn_00587380(object) ? 1 : 13;
                    } else if (fn_004c3f60(object)) operand->registerClass = 2;
                    else operand->registerClass = fn_00581be0(object) ? 14 : 6;
                }
            } else {
                operand->kind = 2; PCODE_VALUE(operand) = PCODE_ARG(int);
                if (instruction->flags & 6) instruction->flags |= 0x20;
            }
            break;
        }
        case 'p': operand->kind = 8; break;
        case 'O': --operand; break;
        default: CError_Internal("PCodeInfo.c", 906);
        }
        while (format[1] && fn_004041a0("@/<>|*", (signed char)format[1])) {
            ++format;
            switch (*format) {
            case '/': if (format[1] == '2') ++format; break;
            case '*': case '<': case '>': case '|':
                if (format[1] == 'p') ++format;
                else if (format[1] && pcode_name_character((signed char)format[1])) {
                    int ignored;
                    format += pcode_const_from_format(format + 1, &ignored);
                } else CError_Internal("PCodeInfo.c", 937);
            }
        }
        ++format;
        if (*format == ']' || *format == ')') ++format;
        ++operand;
    }
    while (operand < end) { operand->kind = 8; ++operand; }
    while (extra--) { operand->kind = 8; ++operand; }
    return instruction;
}


void fn_0058af20(void)
{
    typedef struct Block { struct Block *next; unsigned char unknown04[16]; PCodeInstruction *first; } Block;
    extern Block *pcbasicblocks;
    Block *block;
    PCodeInstruction *instruction;
    for (block = pcbasicblocks; block; block = block->next) {
        for (instruction = block->first; instruction; instruction = instruction->next) {
            if (instruction->flags & 0x1000) {
                int reg = instruction->operands[0].value.reg;
                int cr = instruction->operands[1].value.reg;
                switch (instruction->opcode) {
                case 0x1ed:
                    insertpcodebefore(instruction, makepcode(0x82, reg, cr));
                    insertpcodebefore(instruction, makepcode(0x67, reg, reg,
                        cr * 4 + *(int *)((char *)&instruction->operands[2] + 2) + 1, 31, 31));
                    deletepcode(instruction);
                    break;
                case 0x1ee:
                    insertpcodebefore(instruction, makepcode(0x82, reg, cr));
                    insertpcodebefore(instruction, makepcode(0x67, reg, reg, (cr * 4 + 4) & 31, 28, 31));
                    deletepcode(instruction);
                    break;
                case 0x1ef:
                    insertpcodebefore(instruction, makepcode(0x67, cr, instruction->operands[2].value.reg,
                        ((7 - reg) * 4) & 31, reg * 4, reg * 4 + 3));
                    insertpcodebefore(instruction, makepcode(0x7a, 1 << (7 - reg), cr));
                    deletepcode(instruction);
                    break;
                default:
                    CError_Internal("PCodeInfo.c", 3260);
                }
            }
        }
    }
}

int fn_0058b910(PCodeInstruction *store, PCodeInstruction *load)
{
    int opcode = store->opcode;
    switch (load->opcode) {
    case 0x15: case 0x16: case 0x17: case 0x18:
        switch (opcode) { case 0x28: case 0x29: case 0x2a: case 0x2b: return 2; }
        break;
    case 0x19: case 0x1a: case 0x1b: case 0x1c:
        switch (opcode) { case 0x2c: case 0x2d: case 0x2e: case 0x2f: return 3; }
        break;
    case 0x1d: case 0x1e: case 0x1f: case 0x20:
        switch (opcode) { case 0x2c: case 0x2d: case 0x2e: case 0x2f: return 4; }
        break;
    case 0x22: case 0x23: case 0x24: case 0x25:
        switch (opcode) { case 0x31: case 0x32: case 0x33: case 0x34: return 1; }
        break;
    case 0x8e: case 0x8f: case 0x90: case 0x91:
        switch (opcode) { case 0x96: case 0x97: case 0x98: case 0x99: return 5; }
        break;
    case 0x92: case 0x93: case 0x94: case 0x95:
        switch (opcode) { case 0x9a: case 0x9b: case 0x9c: case 0x9d: return 1; }
        break;
    case 0xf9:
        if (opcode == 0xfe) return 1;
        break;
    case 0x192: case 0x193: case 0x194: case 0x195:
        switch (opcode) {
        case 0x196: case 0x198:
            if (*(short *)((char *)store + 104) == 0x390 && *(short *)((char *)load + 104) == 0x390 &&
                *(int *)((char *)store + 88) == *(int *)((char *)load + 88)) return 1;
        }
        break;
    }
    return 0;
}

int nbytes_loaded_or_stored_by(PCodeInstruction *instruction)
{
    if (pcodeInfoDescriptors[instruction->opcode].flags & 6) {
        switch (instruction->opcode) {
        case 0x15: case 0x16: case 0x17: case 0x18:
        case 0x28: case 0x29: case 0x2a: case 0x2b: return 1;
        case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f: case 0x20: case 0x21:
        case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30: return 2;
        case 0x22: case 0x23: case 0x24: case 0x25: case 0x26:
        case 0x31: case 0x32: case 0x33: case 0x34: case 0x35:
        case 0x8e: case 0x8f: case 0x90: case 0x91:
        case 0x96: case 0x97: case 0x98: case 0x99:
        case 0xba: case 0xbd: case 0xc0: case 0xc1: case 0xc2: case 0xdb: case 0x1e2: return 4;
        case 0x27: case 0x36:
            if (instruction->operands[0].kind == 0 && instruction->operands[0].registerClass == 4)
                return (32 - instruction->operands[0].value.reg) * 4;
            return 128;
        case 0x92: case 0x93: case 0x94: case 0x95:
        case 0x9a: case 0x9b: case 0x9c: case 0x9d: return 8;
        case 0xbb: case 0xbe: return *(int *)((char *)&instruction->operands[2] + 2);
        case 0xbc: case 0xbf: return 128;
        case 0xf4: case 0xfb: return 1;
        case 0xf5: case 0xfc: return 2;
        case 0xf6: case 0xfd: return 4;
        case 0xf7: case 0xf8: case 0xf9: case 0xfa: case 0xfe: case 0xff: return 16;
        case 0x192: case 0x193: case 0x194: case 0x195: case 0x196: case 0x197: case 0x198: case 0x199:
            if (*(short *)((char *)instruction + 104) == 0x390 && *(int *)((char *)instruction + 88) == 1)
                return 4;
            return 8;
        default:
            CError_Internal("PCodeInfo.c", 2995);
        }
    }
    CError_Internal("PCodeInfo.c", 2998);
    return 0;
}

const char *fn_0058ad80(PCodeInstruction *instruction)
{
    if (!(instruction->flags & 0x10000000000000ULL))
        return pcodeInfoDescriptors[instruction->opcode].name;
    fn_00407fd0(pcodeNameBuffer, 40, "%s.", pcodeInfoDescriptors[instruction->opcode].name);
    return pcodeNameBuffer;
}

int fn_0058acf0(PCodeInstruction *instruction, int allowRegisters)
{
    if (instruction->flags & 0x18200000000180ULL) return 0;
    switch (instruction->opcode) {
    case 0x52: case 0x53: case 0x54: case 0x55: case 0xb8: case 0xb9:
        if (!allowRegisters) return 0;
        break;
    case 0x8a:
        if (instruction->operands[1].kind == 4) break;
    case 0x89:
        if (!allowRegisters) return 0;
        if (instruction->operands[0].value.reg < first_temporary_register ||
            instruction->operands[0].value.reg > last_temporary_register) return 0;
        break;
    }
    return 1;
}

int fn_0058ba80(PCodeInstruction *instruction)
{
    switch (instruction->opcode) {
    case 0x89: case 0x8a: case 0x160: case 0x161: case 0x162:
        return 1;
    case 0x3f:
        if (instruction->operands[2].kind == 4) return 1;
    case 0x42:
        if (instruction->opcode == 0x42 && instruction->operands[2].kind == 4 &&
            instruction->operands[2].registerClass == 8) return 1;
    case 0x58: case 0x59:
        return instruction->operands[1].value.reg == 13 || instruction->operands[1].value.reg == 2 ||
            instruction->operands[1].value.reg == pcodeSpecialBaseRegister;
    case 0x22:
        if (instruction->operands[1].value.reg == 1 && instruction->operands[2].kind == 2 &&
            *(int *)((char *)&instruction->operands[2] + 2) == 0) return 1;
    }
    return 0;
}

int fn_0058b870(PCodeInstruction *instruction)
{
    switch (instruction->opcode) {
    case 0x15: case 0x16: case 0x17: case 0x18: return 2;
    case 0x19: case 0x1a: case 0x1b: case 0x1c: return 3;
    case 0x1d: case 0x1e: case 0x1f: case 0x20: return 4;
    case 0x22: case 0x23: case 0x24: case 0x25: return 1;
    case 0x8e: case 0x8f: case 0x90: case 0x91: return 5;
    case 0x92: case 0x93: case 0x94: case 0x95: return 1;
    case 0xf9: return 1;
    case 0x192: case 0x193: case 0x194: case 0x195: return 1;
    }
    return 0;
}

int copy_opcode_for_type(void *type)
{
    unsigned char *t = type;
    switch (fn_00579560(type)) {
    case 4:
        if (pcodeFloatOption && t[0] == 2 && t[6] < 0x17 && *(int *)(t + 2) != 4)
            CError_Internal("PCodeInfo.c", 3144);
        else if (((t[0] == 1 && t[6] < 0x17) || t[0] == 4) && *(int *)(t + 2) == 8)
            CError_Internal("PCodeInfo.c", 3144);
        return 0x8b;
    case 3:
        if (pcodeProcessor == 0x16 && t[0] == 2 && t[6] == 0x19) return 0x1a8;
        return 0x9e;
    case 2: return 0x190;
    case 1: return 0x76;
    }
    CError_Internal("PCodeInfo.c", 3164);
    return 0x8c;
}


int is_valid_displ(PCodeInstruction *instruction, void *object, int displacement)
{
    if (object) {
        if (((unsigned char *)object)[2] != 1) return 0;
        displacement += fn_00587410(object);
    }
    if (instruction->flags & 0x80000000000ULL) {
        switch (instruction->opcode) {
        case 0x192: case 0x193: case 0x196: case 0x197:
            return displacement >= -2048 && displacement <= 2047;
        default:
            return 0;
        }
    }
    if (!(instruction->flags & 0x400000000000ULL) && displacement == (short)displacement) return 1;
    return 0;
}

PCodeInstruction *makecopyinstruction(PCodeOperand *source, PCodeOperand *destination)
{
    if (destination->kind == 0) {
        switch ((signed char)destination->registerClass) {
        case 4:
            return makepcode(0x8b, destination->value.reg, source->value.reg);
        case 3:
            if ((source->flags & 0x8000) || (source->flags & 0x4000) || (source->flags & 0xc000))
                return makepcode(0x1a8, destination->value.reg, source->value.reg);
            return makepcode(0x9e, destination->value.reg, source->value.reg);
        case 2:
            return makepcode(0x190, destination->value.reg, source->value.reg);
        case 1:
            return makepcode(0x76, destination->value.reg, source->value.reg);
        }
    }
    CError_Internal("PCodeInfo.c", 2357);
    return 0;
}

PCodeOperand *fn_0058aec0(PCodeInstruction *instruction)
{
    int i;
    if (instruction->flags & 9) {
        for (i = 0; i < instruction->operandCount; ++i)
            if (instruction->operands[i].kind == 6) return &instruction->operands[i];
        return 0;
    }
    return 0;
}

unsigned char fn_0058add0(PCodeInstruction *instruction)
{
    return fn_0058aec0(instruction) != 0;
}

PCodeInstruction *fn_0058ae30(void *label)
{
    return makepcode(0, label);
}

void fn_0058ae40(PCodeInstruction *instruction, void *label)
{
    PCodeOperand *operand = fn_0058aec0(instruction);
    if (!operand || operand->kind != 6) CError_Internal("PCodeInfo.c", 3301);
    *(void **)((char *)operand + 2) = label;
}

void change_num_operands(PCodeInstruction *instruction, int count)
{
    int i;
    short oldCount = instruction->operandCount;
    int capacity = oldCount > 6 ? oldCount : 6;
    if (capacity < count)
        CError_Internal("PCodeInfo.c", 3010);
    for (i = instruction->operandCount - 1; i >= count; --i)
        instruction->operands[i].kind = 8;
    instruction->operandCount = count;
}

void change_opcode(PCodeInstruction *instruction, short opcode)
{
    PCodeFlags oldFlags = instruction->flags;
    int oldRecord = (oldFlags & 0x10000000000000ULL) != 0;
    PCodeFlags newFlags = pcodeInfoDescriptors[opcode].flags;
    int newRecord = (newFlags & 0x10000000000000ULL) != 0;
    newFlags &= ~0x20ULL;
    oldFlags &= ~(pcodeInfoDescriptors[instruction->opcode].flags & ~0x20ULL);
    instruction->flags = oldFlags | newFlags;
    if ((instruction->flags & 0x10) && (instruction->flags & 0x10000000000000ULL))
        instruction->flags &= ~0x10ULL;
    if (oldRecord && oldRecord != newRecord) {
        if (newFlags & 0x2000000000000ULL) pcsetrecordbit(instruction);
        else CError_Internal("PCodeInfo.c", 3049);
    } else if (newRecord && !oldRecord) {
        pcsetrecordbit(instruction);
    }
    instruction->opcode = opcode;
}

PCodeInstruction *makecopyforload(PCodeInstruction *context, int category, PCodeOperand *source, PCodeOperand *destination)
{
    switch (category) {
    case 1: return makecopyinstruction(source, destination);
    case 2: return makepcode(0x67, destination->value.reg, source->value.reg, 0, 24, 31);
    case 3: return makepcode(0x67, destination->value.reg, source->value.reg, 0, 16, 31);
    case 4: return makepcode(0x65, destination->value.reg, source->value.reg);
    case 5: return makepcode(0xb5, destination->value.reg, source->value.reg);
    }
    CError_Internal("PCodeInfo.c", 2746);
    return 0;
}
