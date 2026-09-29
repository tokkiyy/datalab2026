/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~(x & ~y) & ~(~x & y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y)
{
    int sx = x >> 31;
    int sy = y >> 31;

    return !(sx ^ sy) & (!((!x) ^ (!y)));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v)
{
    int r = 0;

    r = r + ((!!(v >> 16)) << 4);
    v = v >> r;

    r = r + ((!!(v >> 8)) << 3);
    v = v >> ((!!(v >> 8)) << 3);

    r = r + ((!!(v >> 4)) << 2);
    v = v >> ((!!(v >> 4)) << 2);

    r = r + ((!!(v >> 2)) << 1);
    v = v >> ((!!(v >> 2)) << 1);

    r = r + (!!(v >> 1));

    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m)
{
    int bn = (x >> (n << 3)) & 0xff;
    int bm = (x >> (m << 3)) & 0xff;

    int mask = (0xff << (n << 3)) |
               (0xff << (m << 3));

    x = x & ~mask;

    x = x | (bn << (m << 3))
          | (bm << (n << 3));

    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v)
{
    unsigned mask1 = 0x55555555;
    unsigned mask2 = 0x33333333;
    unsigned mask3 = 0x0f0f0f0f;
    unsigned mask4 = 0x00ff00ff;

    // 交换相邻1bit
    v = ((v >> 1) & mask1) | ((v & mask1) << 1);

    // 交换相邻2bit
    v = ((v >> 2) & mask2) | ((v & mask2) << 2);

    // 交换相邻4bit
    v = ((v >> 4) & mask3) | ((v & mask3) << 4);

    // 交换相邻8bit
    v = ((v >> 8) & mask4) | ((v & mask4) << 8);

    // 交换16bit
    v = (v >> 16) | (v << 16);

    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n)
{
    int mask = ~(((1 << 31) >> n) << 1);

    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x)
{
    int n = 0;

    // 统计 ~x 的前导0数量
    x = ~x;

    int b16 = !(x >> 16);
    n += b16 << 4;
    x <<= b16 << 4;

    int b8 = !(x >> 24);
    n += b8 << 3;
    x <<= b8 << 3;

    int b4 = !(x >> 28);
    n += b4 << 2;
    x <<= b4 << 2;

    int b2 = !(x >> 30);
    n += b2 << 1;
    x <<= b2 << 1;

    n += !(x >> 31);

    // 处理 x 原来全1的情况
    return n + !x;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x)
{
    unsigned sign = 0;

    if (x == 0)
        return 0;

    if (x == 0x80000000)
        return 0xcf000000;


    if (x < 0)
    {
        sign = 0x80000000;
        x = -x;
    }


    int pos = 31;

    while (!(x & (1 << pos)))
        pos--;


    int exp = pos + 127;


    unsigned frac;


    if (pos <= 23)
    {
        frac = x << (23 - pos);
    }
    else
    {
        int shift = pos - 23;

        frac = x >> shift;


        unsigned rest = x & ((1 << shift) - 1);

        unsigned half = 1 << (shift - 1);


        if (rest > half || 
           (rest == half && (frac & 1)))
        {
            frac++;
        }


        if (frac == (1 << 24))
        {
            exp++;
            frac >>= 1;
        }
    }


    frac &= 0x7fffff;


    return sign | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf)
{
    unsigned sign = uf & 0x80000000;
    unsigned exp = uf & 0x7F800000;
    unsigned frac = uf & 0x007FFFFF;


    // NaN or infinity
    if (exp == 0x7F800000)
        return uf;


    // denormalized
    if (exp == 0)
    {
        frac <<= 1;

        // becomes normalized
        if (frac & 0x00800000)
        {
            exp = 0x00800000;
            frac &= 0x007FFFFF;
        }

        return sign | exp | frac;
    }


    // normal number
    exp += 0x00800000;


    // overflow
    if (exp == 0x7F800000)
        frac = 0;


    return sign | exp | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {

    // uf2 是高32位
    unsigned high = uf2;
    unsigned low = uf1;


    int sign = high >> 31;

    int exp = (high >> 20) & 0x7FF;


    unsigned frac_high = high & 0xFFFFF;


    if (exp == 0x7FF)
        return 0x80000000;


    int E = exp - 1023;


    if (E < 0)
        return 0;


    if (E > 31)
        return 0x80000000;


    unsigned long long frac =
        ((unsigned long long)frac_high << 32) | low;


    // 加隐藏位
    frac |= (1ULL << 52);


    unsigned long long result;


    if(E >= 52)
    result = frac << (E - 52);
    else
    result = frac >> (52 - E);


    if (sign)
        return -result;

    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x)
{
    // too small: 2^x < 2^-149
    if (x < -149)
        return 0;


    // too large: overflow to +infinity
    if (x > 127)
        return 0x7F800000;


    // denormalized numbers
    if (x < -126)
        return 1 << (x + 149);


    // normalized numbers
    return (x + 127) << 23;
}
