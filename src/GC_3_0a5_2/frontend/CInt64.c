#define CERROR_FILE "CInt64.c"
#include "compiler/common.h"
#include "GC_3_0a5_2/compiler/CInt64.h"

static inline SInt32 compare_unsigned_words(CInt64 *a, CInt64 *b)
{
    if (a->hi == b->hi) {
        if (a->lo < b->lo)
            return -1;
        if (a->lo > b->lo)
            return 1;
        return 0;
    }
    if ((UInt32)a->hi < (UInt32)b->hi)
        return -1;
    return 1;
}


void CInt64_ConvertUInt8(CInt64 *value)
{
    value->lo = (UInt8)value->lo;
    value->hi = 0;
}

void CInt64_ConvertInt8(CInt64 *value)
{
    SInt32 high;
    value->lo = (signed char)value->lo;
    if (value->lo & 0x80000000)
        high = -1;
    else
        high = 0;
    value->hi = high;
}

void CInt64_ConvertUInt16(CInt64 *value)
{
    value->lo = (UInt16)value->lo;
    value->hi = 0;
}

void CInt64_ConvertInt16(CInt64 *value)
{
    SInt32 high;
    value->lo = (SInt16)value->lo;
    if (value->lo & 0x80000000)
        high = -1;
    else
        high = 0;
    value->hi = high;
}

void CInt64_ConvertUInt32(CInt64 *value)
{
    value->hi = 0;
}

void CInt64_ConvertInt32(CInt64 *value)
{
    SInt32 high;
    if (value->lo & 0x80000000)
        high = -1;
    else
        high = 0;
    value->hi = high;
}

CInt64 CInt64_Or(CInt64 left, CInt64 right)
{
    left.hi |= right.hi;
    left.lo |= right.lo;
    return left;
}

CInt64 CInt64_Xor(CInt64 left, CInt64 right)
{
    left.hi ^= right.hi;
    left.lo ^= right.lo;
    return left;
}

/* Static constants retained under their names in the GC3 symbols. */
static const CInt64 cint64_negone = {-1, 0xffffffff};
static const CInt64 cint64_one = {0, 1};
static const CInt64 cint64_max = {0x7fffffff, 0xffffffff};
static const CInt64 cint64_min = {0x80000000, 0};
static inline CInt64 mask_xor(CInt64 v, CInt64 m)
{
    v.hi ^= m.hi;
    v.lo ^= m.lo;
    return v;
}

static inline CInt64 xorWords(CInt64 value, CInt64 mask)
{
    value.hi ^= mask.hi;
    value.lo ^= mask.lo;
    return value;
}

static inline CInt64 xor64(CInt64 p, CInt64 q)
{
    p.hi ^= q.hi;
    p.lo ^= q.lo;
    return p;
}

static inline SInt32 compare_u64(UInt32 a_hi, UInt32 a_lo, UInt32 b_hi, UInt32 b_lo)
{
    if (a_hi == b_hi) {
        if (a_lo < b_lo)
            return -1;
        if (a_lo <= b_lo)
            return 0;
    } else if (a_hi < b_hi) {
        return -1;
    }
    return 1;
}

static inline CInt64 xor_key(CInt64 a, CInt64 b)
{
    a.hi ^= b.hi;
    a.lo ^= b.lo;
    return a;
}

static inline CInt64 unmask(CInt64 v, CInt64 k)
{
    v.hi ^= k.hi;
    v.lo ^= k.lo;
    return v;
}

CInt64 CInt64_And(CInt64 left, CInt64 right)
{
    left.hi &= right.hi;
    left.lo &= right.lo;
    return left;
}

Boolean CInt64_IsInURange(CInt64 n, SInt16 kind)
{
    SInt32 hi = n.hi;
    UInt32 lo = n.lo;
    switch (kind) {
        case 1:
            return hi == 0 && (lo & 0xffffff00) == 0;
        case 2:
            return hi == 0 && (lo & 0xffff0000) == 0;
        case 4:
            return hi == 0;
        case 8:
            return 1;
        default:
            return 0;
    }
}

unsigned char CInt64_IsInRange(CInt64 value, short byteSize)
{
    CInt64 bound;
    if ((char)((value.hi & (-2147483647 - 1)) != 0) != 0) {
        CInt64 biasedBound, biasedValue;
        switch (byteSize) {
            case 1:
                bound.lo = -128;
                bound.hi = -1;
                break;
            case 2:
                bound.lo = -32768;
                bound.hi = -1;
                break;
            case 4:
                bound.lo = (-2147483647 - 1);
                bound.hi = -1;
                break;
            case 8:
                return 1;
            default:
                return 0;
        }
        biasedValue = xorWords(value, cint64_min);
        biasedBound = xorWords(bound, cint64_min);
        return compare_unsigned_words(&biasedValue, &biasedBound) >= 0;
    }
    {
        CInt64 biasedBound, biasedValue;
        switch (byteSize) {
            case 1:
                bound.lo = 127;
                bound.hi = 0;
                break;
            case 2:
                bound.lo = 32767;
                bound.hi = 0;
                break;
            case 4:
                bound.lo = 2147483647;
                bound.hi = 0;
                break;
            case 8:
                return 1;
            default:
                return 0;
        }
        biasedValue = xorWords(value, cint64_min);
        biasedBound = xorWords(bound, cint64_min);
        return compare_unsigned_words(&biasedValue, &biasedBound) <= 0;
    }
}

Boolean CInt64_NotEqual(CInt64 a, CInt64 b)
{
    return a.hi != b.hi || a.lo != b.lo;
}

unsigned char CInt64_Equal(CInt64 left, CInt64 right)
{
    return left.hi == right.hi && left.lo == right.lo;
}


Boolean CInt64_GreaterEqualU(CInt64 x, CInt64 y)
{
    int comparison;

    if (x.hi == y.hi) {
        if (x.lo < y.lo)
            comparison = -1;
        else if (x.lo > y.lo)
            comparison = 1;
        else
            comparison = 0;
    } else if ((UInt32)x.hi < (UInt32)y.hi)
        comparison = -1;
    else
        comparison = 1;

    return comparison >= 0;
}

Boolean CInt64_GreaterEqual(CInt64 a, CInt64 b)
{
    CInt64 x, y;
    x = xor64(a, cint64_min);
    y = xor64(b, cint64_min);
    return compare_unsigned_words(&x, &y) >= 0;
}

Boolean CInt64_LessEqualU(CInt64 x, CInt64 y)
{
    int comparison;

    if (x.hi == y.hi) {
        if (x.lo < y.lo)
            comparison = -1;
        else if (x.lo > y.lo)
            comparison = 1;
        else
            comparison = 0;
    } else if ((UInt32)x.hi < (UInt32)y.hi)
        comparison = -1;
    else
        comparison = 1;

    return comparison <= 0;
}

Boolean CInt64_LessEqual(CInt64 a, CInt64 b)
{
    CInt64 x, y;
    x = xor64(a, cint64_min);
    y = xor64(b, cint64_min);
    return compare_unsigned_words(&x, &y) <= 0;
}

Boolean CInt64_GreaterU(CInt64 x, CInt64 y)
{
    int comparison;

    if (x.hi == y.hi) {
        if (x.lo < y.lo)
            comparison = -1;
        else if (x.lo > y.lo)
            comparison = 1;
        else
            comparison = 0;
    } else if ((UInt32)x.hi < (UInt32)y.hi)
        comparison = -1;
    else
        comparison = 1;

    return comparison > 0;
}

Boolean CInt64_Greater(CInt64 a, CInt64 b)
{
    CInt64 x;
    CInt64 y;

    x = xor_key(a, cint64_min);
    y = xor_key(b, cint64_min);
    return compare_unsigned_words(&x, &y) > 0;
}

Boolean CInt64_LessU(CInt64 a, CInt64 b)
{
    SInt32 comparison;

    if (a.hi == b.hi) {
        if (a.lo < b.lo)
            comparison = -1;
        else if (a.lo > b.lo)
            comparison = 1;
        else
            comparison = 0;
    } else {
        if ((UInt32)a.hi < (UInt32)b.hi)
            comparison = -1;
        else
            comparison = 1;
    }
    return comparison < 0;
}

Boolean CInt64_Less(CInt64 a, CInt64 b)
{
    CInt64 x;
    CInt64 y;
    x = unmask(a, cint64_min);
    y = unmask(b, cint64_min);
    return compare_unsigned_words(&x, &y) < 0;
}

CInt64 CInt64_ShrU(CInt64 value, CInt64 count)
{
    UInt32 hi, lo, i;

    if (count.hi == 0 && count.lo < 64) {
        hi = (UInt32)value.hi;
        lo = value.lo;
        i = count.lo;
        while (i != 0) {
            lo >>= 1;
            if (hi & 1)
                lo |= 0x80000000;
            hi >>= 1;
            i--;
        }
        value.hi = (SInt32)hi;
        value.lo = lo;
    } else {
        value.hi = 0;
        value.lo = 0;
    }
    return value;
}

CInt64 CInt64_Shr(CInt64 value, CInt64 count)
{
    if (count.hi == 0 && count.lo < 64) {
        SInt32 hi;
        UInt32 lo;
        UInt32 n;
        hi = value.hi;
        lo = value.lo;
        n = count.lo;
        while (n != 0) {
            lo = lo >> 1;
            if (hi & 1)
                lo = lo | 0x80000000;
            hi = hi >> 1;
            n--;
        }
        value.hi = hi;
        value.lo = lo;
    } else {
        Boolean neg = (value.hi & 0x80000000) != 0;
        if (neg) {
            value.hi = -1;
            value.lo = 0xffffffff;
        } else {
            value.hi = 0;
            value.lo = 0;
        }
    }
    return value;
}

CInt64 CInt64_Shl(CInt64 v, CInt64 count)
{
    SInt32 hi;
    UInt32 lo;
    UInt32 n;
    if (count.hi == 0 && count.lo < 0x40) {
        hi = v.hi;
        lo = v.lo;
        n = count.lo;
        while (n != 0) {
            hi <<= 1;
            if (lo & 0x80000000) {
                hi |= 1;
            }
            lo <<= 1;
            n--;
        }
        v.hi = hi;
        v.lo = lo;
    } else {
        v.hi = 0;
        v.lo = 0;
    }
    return v;
}

CInt64 CInt64_ModU(CInt64 a, CInt64 b)
{
    CInt64 result;
    CInt64_DivMod(&a, &b, NULL, &result);
    return result;
}

static inline Boolean CInt64_IsNeg(SInt32 hi)
{
    return (hi & 0x80000000) != 0;
}

static inline CInt64 recovered_complement_CInt64_Neg(CInt64 x)
{
    CInt64 y;
    y.hi = ~x.hi;
    y.lo = ~x.lo;
    return y;
}

static inline CInt64 negate_mod_operand(CInt64 x)
{
    CInt64 recovered_result;
    recovered_result = CInt64_Add(recovered_complement_CInt64_Neg(x), cint64_one);
    return recovered_result;
}

CInt64 CInt64_Mod(CInt64 a, CInt64 b)
{
    CInt64 r;
    if (CInt64_IsNeg(a.hi)) {
        a = negate_mod_operand(a);
        if (CInt64_IsNeg(b.hi))
            b = negate_mod_operand(b);
        CInt64_DivMod(&a, &b, NULL, &r);
        return negate_mod_operand(r);
    }
    if (CInt64_IsNeg(b.hi))
        b = negate_mod_operand(b);
    CInt64_DivMod(&a, &b, NULL, &r);
    return r;
}

CInt64 CInt64_DivU(CInt64 a, CInt64 b)
{
    CInt64 result;
    CInt64_DivMod(&a, &b, &result, NULL);
    return result;
}

static inline CInt64 recovered_complement_Neg(CInt64 x)
{
    CInt64 y;
    y.hi = ~x.hi;
    y.lo = ~x.lo;
    return y;
}

static inline CInt64 Neg(CInt64 x)
{
    CInt64 r;
    r = CInt64_Add(recovered_complement_Neg(x), cint64_one);
    return r;
}

CInt64 CInt64_Div(CInt64 dividend, CInt64 divisor)
{
    CInt64 quotient;
    Boolean divisorNegative, dividendNegative;

    divisorNegative = (divisor.hi & 0x80000000) != 0;
    if (divisorNegative) {
        divisor = Neg(divisor);
        dividendNegative = (dividend.hi & 0x80000000) != 0;
        if (dividendNegative) {
            dividend = Neg(dividend);
            CInt64_DivMod(&dividend, &divisor, &quotient, NULL);
            return quotient;
        }
        CInt64_DivMod(&dividend, &divisor, &quotient, NULL);
        return Neg(quotient);
    } else {
        dividendNegative = (dividend.hi & 0x80000000) != 0;
        if (dividendNegative) {
            dividend = Neg(dividend);
            CInt64_DivMod(&dividend, &divisor, &quotient, NULL);
            return Neg(quotient);
        }
        CInt64_DivMod(&dividend, &divisor, &quotient, NULL);
        return quotient;
    }
}

static inline Boolean iszero(const CInt64 *n)
{
    return n->hi == 0 && n->lo == 0;
}

static inline CInt64 inv(CInt64 input)
{
    CInt64 output;
    output.hi = ~input.hi;
    output.lo = ~input.lo;
    return output;
}

static inline CInt64 neg(CInt64 input)
{
    CInt64 result;
    result = CInt64_Add(inv(input), cint64_one);
    return result;
}

static inline CInt64 sub(CInt64 lhs, CInt64 rhs)
{
    lhs = CInt64_Add(lhs, neg(rhs));
    return lhs;
}

void CInt64_DivMod(const CInt64 *lhs, const CInt64 *rhs, CInt64 *pDiv, CInt64 *pMod)
{
    UInt32 workF;
    Boolean bad;
    UInt32 workA;
    UInt32 workB;
    UInt32 workC;
    UInt32 workD;
    UInt32 workE;
    UInt32 workG;
    UInt32 workH;
    int counter;
    CInt64 work;

    bad = iszero(rhs);
    if (bad)
        return;

    workF = 0;
    workB = lhs->hi;
    workA = lhs->lo;
    workC = rhs->hi;
    workE = 0;
    workD = rhs->lo;
    workG = 0;
    workH = 0;
    for (counter = 0; counter < 64; counter++) {
        workF <<= 1;
        if (workE & 0x80000000)
            workF |= 1;
        workE <<= 1;
        if (workB & 0x80000000)
            workE |= 1;
        workB <<= 1;
        if (workA & 0x80000000)
            workB |= 1;
        workA <<= 1;
        workG <<= 1;
        if (workH & 0x80000000)
            workG |= 1;
        workH <<= 1;
        if (workF > workC || (workF == workC && workE >= workD)) {
            workH |= 1;
            work.hi = workF;
            work.lo = workE;
            work = sub(work, *rhs);
            workF = work.hi;
            workE = work.lo;
        }
    }
    if (pDiv) {
        pDiv->hi = workG;
        pDiv->lo = workH;
    }
    if (pMod) {
        pMod->hi = workF;
        pMod->lo = workE;
    }
}

static inline Boolean isneg(CInt64 x)
{
    return (x.hi & 0x80000000) != 0;
}

static inline CInt64 recovered_complement_lneg(CInt64 x)
{
    CInt64 nx;
    nx.hi = ~x.hi;
    nx.lo = ~x.lo;
    return nx;
}

static inline CInt64 lneg(CInt64 x)
{
    CInt64 recovered_result;
    recovered_result = CInt64_Add(recovered_complement_lneg(x), cint64_one);
    return recovered_result;
}

CInt64 CInt64_Mul(CInt64 a, CInt64 b)
{
    if (isneg(b)) {
        if (isneg(a)) {
            return CInt64_MulU(lneg(a), lneg(b));
        } else {
            return lneg(CInt64_MulU(a, lneg(b)));
        }
    } else {
        if (isneg(a)) {
            return lneg(CInt64_MulU(lneg(a), b));
        } else {
            return CInt64_MulU(a, b);
        }
    }
}

CInt64 CInt64_MulU(CInt64 lhs, CInt64 rhs)
{
    CInt64 result;
    CInt64 work1;
    UInt32 aaaa;
    UInt32 bbbb;
    UInt32 cccc;
    UInt32 dddd;
    UInt32 eeee;

    eeee = dddd = rhs.lo;
    result.lo = 0;
    result.hi = 0;
    bbbb = lhs.lo;
    cccc = rhs.hi;
    while (bbbb != 0) {
        if (bbbb & 1) {
            work1.hi = cccc;
            work1.lo = dddd;
            result = CInt64_Add(result, work1);
        }
        cccc <<= 1;
        if (dddd & 0x80000000)
            cccc |= 1;
        bbbb >>= 1;
        dddd <<= 1;
    }
    aaaa = lhs.hi;
    while (aaaa != 0 && eeee != 0) {
        if (aaaa & 1)
            result.hi += eeee;
        eeee <<= 1;
        aaaa >>= 1;
    }
    return result;
}

static inline CInt64 not64(CInt64 v)
{
    CInt64 t;
    t.hi = ~v.hi;
    t.lo = ~v.lo;
    return t;
}

CInt64 CInt64_Neg(CInt64 x)
{
    CInt64 r;
    r = CInt64_Add(not64(x), cint64_one);
    return r;
}

CInt64 CInt64_Inv(CInt64 input)
{
    CInt64 output;
    output.hi = ~input.hi;
    output.lo = ~input.lo;
    return output;
}

CInt64 CInt64_Not(CInt64 input)
{
    CInt64 output;
    long value = (Boolean)(input.hi == 0 && input.lo == 0);
    output.lo = value;
    output.hi = value < 0 ? -1 : 0;
    return output;
}

CInt64 CInt64_Sub(CInt64 lhs, CInt64 rhs)
{
    CInt64 t;
    t = CInt64_Add(inv(rhs), cint64_one);
    lhs = CInt64_Add(lhs, t);
    return lhs;
}

CInt64 CInt64_Add(CInt64 a, CInt64 b)
{
    if (a.lo & 0x80000000) {
        if (b.lo & 0x80000000) {
            a.lo += b.lo;
            a.hi += 1;
        } else {
            a.lo += b.lo;
            if (!(a.lo & 0x80000000))
                a.hi += 1;
        }
    } else {
        if (b.lo & 0x80000000) {
            a.lo += b.lo;
            if (!(a.lo & 0x80000000))
                a.hi += 1;
        } else {
            a.lo += b.lo;
        }
    }
    a.hi += b.hi;
    return a;
}


static inline Boolean negative_words(const CInt64 *v)
{
    return (v->hi & 0x80000000) != 0;
}

static inline CInt64 modu(CInt64 lhs, CInt64 rhs)
{
    CInt64 result;
    CInt64 *a = &lhs;
    CInt64 *b = &rhs;
    CInt64 *r = &result;
    CInt64_DivMod(a, b, NULL, r);
    return result;
}

static inline CInt64 divu(CInt64 lhs, CInt64 rhs)
{
    CInt64 result;
    CInt64 *a = &lhs;
    CInt64 *b = &rhs;
    CInt64 *r = &result;
    CInt64_DivMod(a, b, r, NULL);
    return result;
}

extern double CInt64_ConvertUToLongDouble(CInt64 *);
extern void CInt64_ConvertUFromLongDouble(CInt64 *, double);
int CInt64_PrintDec(char *output, CInt64 num)
{
    int length;
    CInt64 rem;
    CInt64 divisor;
    char buf[32];
    char *bufp;

    length = 0;
    if (negative_words(&num)) {
        num = neg(num);
        *output = '-';
        output++;
        length++;
    }

    if (!iszero(&num)) {
        divisor.lo = 10;
        divisor.hi = 0;

        bufp = buf;
        for (;;) {
            rem = modu(num, divisor);
            *(bufp++) = rem.lo + '0';
            num = divu(num, divisor);
            if (iszero(&num) != 0)
                break;
        }

        while (--bufp >= buf) {
            *(output++) = *bufp;
            length++;
        }
    } else {
        *(output++) = '0';
        length++;
    }

    *output = 0;
    return length;
}

char *CInt64_ScanBinString(CInt64 *value, char *digits, unsigned char *overflow)
{
    UInt32 high;
    Boolean bit;
    UInt32 low;
    char digit;
    *overflow = 0;
    value->lo = 0;
    value->hi = 0;
    do {
        digit = *digits;
        if (digit == '0')
            bit = FALSE;
        else if (digit == '1')
            bit = TRUE;
        else
            break;
        high = value->hi;
        ++digits;
        low = value->lo;
        if ((high & 0x80000000) != 0)
            *overflow = 1;
        high = high << 1;
        if ((low & 0x80000000) != 0)
            high |= 1;
        value->hi = high;
        value->lo = low << 1;
        if (bit == TRUE)
            *value = CInt64_Add(*value, cint64_one);
    } while (TRUE);
    return digits;
}

char *CInt64_ScanHexString(CInt64 *value, char *p, Boolean *overflow)
{
    SInt8 digit;
    SInt32 n;
    UInt32 hi, lo;
    CInt64 d;

    *overflow = 0;
    value->lo = 0;
    value->hi = 0;
    for (;;) {
        digit = *p;
        if (digit >= '0' && digit <= '9')
            digit -= '0';
        else if (digit >= 'A' && digit <= 'F')
            digit -= 'A' - 10;
        else if (digit >= 'a' && digit <= 'f')
            digit -= 'a' - 10;
        else
            break;

        hi = value->hi;
        p++;
        lo = value->lo;
        if (hi & 0xf0000000)
            *overflow = 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        value->hi = hi;
        value->lo = lo;

        n = digit;
        d.lo = n;
        hi = n < 0 ? -1 : 0;
        d.hi = hi;
        *value = CInt64_Add(*value, d);
    }
    return p;
}

char *CInt64_ScanOctString(CInt64 *val, char *s, Boolean *overflow)
{
    char c;
    UInt32 hi;
    UInt32 lo;
    SInt32 digit;
    CInt64 d;
    *overflow = 0;
    val->lo = 0;
    val->hi = 0;
    while (*s >= '0' && *s <= '7') {
        c = *s;
        hi = val->hi;
        lo = val->lo;
        if (hi & 0xE0000000)
            *overflow = 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        val->hi = hi;
        val->lo = lo;
        digit = c - '0';
        d.lo = digit;
        d.hi = digit < 0 ? -1 : 0;
        *val = CInt64_Add(*val, d);
        s++;
    }
    return s;
}

UInt8 *CInt64_ScanDecString(CInt64 *v, char *s, Boolean *ovf)
{
    CInt64 t;
    char c;
    SInt32 hi;
    UInt32 lo;
    *ovf = 0;
    v->lo = 0;
    v->hi = 0;
    while ((c = *s) >= '0' && c <= '9') {
        hi = v->hi;
        lo = v->lo;
        if (hi & 0xe0000000)
            *ovf = 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        t.hi = hi;
        t.lo = lo;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        v->hi = hi;
        v->lo = lo;
        if (negative_words(v)) {
            *v = CInt64_Add(*v, t);
            if (!negative_words(v))
                *ovf = 1;
        } else {
            *v = CInt64_Add(*v, t);
        }
        t.lo = c - '0';
        t.hi = c - '0' < 0 ? -1 : 0;
        if (negative_words(v)) {
            *v = CInt64_Add(*v, t);
            if (!negative_words(v))
                *ovf = 1;
        } else {
            *v = CInt64_Add(*v, t);
        }
        s++;
    }
    return (UInt8 *)s;
}

#pragma options align = mac68k
static Boolean data_006e1c28;
static float data_006e1c2a;
static float data_006e1c2e[65];
#pragma options align = reset

/* These Windows LongDouble entry points use eight-byte floating arguments. */
typedef struct { float value; } GC3CInt64Power;
static const double cint64_float_one = 1.0;
static const double cint64_float_zero = 0.0;
double CInt64_ConvertToLongDouble(CInt64 *val)
{
    CInt64 tmp;
    if (negative_words(val)) {
        tmp = neg(*val);
        return -CInt64_ConvertUToLongDouble(&tmp);
    }
    return CInt64_ConvertUToLongDouble(val);
}

double CInt64_ConvertUToLongDouble(CInt64 *v)
{
    double result;
    Boolean iszero;
    SInt32 word;
    int i;

    iszero = (v->hi == 0 && v->lo == 0);
    if (iszero)
        return 0.0;

    result = 0.0;

    word = v->hi;
    if (word != 0) {
        i = 0;
        do {
            result += result;
            if (word & 0x80000000)
                result += cint64_float_one;
            i++;
            word <<= 1;
        } while (i < 32);
    }

    word = v->lo;
    i = 0;
    do {
        result += result;
        if (word & 0x80000000)
            result = result + cint64_float_one;
        i++;
        word <<= 1;
    } while (i < 32);

    return result;
}

void CInt64_ConvertFromLongDouble(CInt64 *p, double x)
{
    CInt64 r, v, w;
    if (x < cint64_float_zero) {
        CInt64_ConvertUFromLongDouble(p, -x);
        v = *p;
        w.hi = ~v.hi, w.lo = ~v.lo;
        r = CInt64_Add(w, cint64_one);
        *p = r;
    } else {
        CInt64_ConvertUFromLongDouble(p, x);
    }
}

static inline float power_of_two(short n)
{
    int i;

    if (!data_006e1c28) {
        data_006e1c2a = 1.0f;
        i = 0;
        do {
            data_006e1c2e[i] = data_006e1c2a;
            data_006e1c2a += data_006e1c2a;
        } while (++i < 65);
        data_006e1c28 = 1;
    }
    return data_006e1c2e[n];
}

static inline void get_power_of_two(GC3CInt64Power *result, short n)
{
    int i;

    if (!data_006e1c28) {
        data_006e1c2a = 1.0f;
        i = 0;
        do {
            data_006e1c2e[i] = data_006e1c2a;
            data_006e1c2a += data_006e1c2a;
        } while (++i < 65);
        data_006e1c28 = 1;
    }
    result->value = data_006e1c2e[n];
}

void CInt64_ConvertUFromLongDouble(CInt64 *result, double value)
{
    UInt32 hi, lo;
    int bit;
    GC3CInt64Power power;

    power.value = 0.0;
    if (value <= cint64_float_zero) {
        result->hi = 0;
        result->lo = 0;
        return;
    }
    if (value >= power_of_two(64)) {
        result->hi = 0xffffffff;
        result->lo = 0xffffffff;
        return;
    }
    hi = lo = 0;
    bit = 63;
    do {
        hi <<= 1;
        if (lo & 0x80000000)
            hi |= 1;
        lo <<= 1;
        get_power_of_two(&power, bit);
        if (power.value <= value) {
            lo |= 1;
            value -= power.value;
        }
    } while (--bit >= 0);
    result->hi = hi;
    result->lo = lo;
}

void CInt64_Init(void)
{
}
