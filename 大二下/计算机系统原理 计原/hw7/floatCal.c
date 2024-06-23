#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned long dwrd; // 32 - bit
union
{
    float f; //仅作验证之用
    long d;  // 32-bit
} u, v, w, z;
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
void printCode(long code, int length)
{
    puts("");
    for (int i = 0; i < length; i++)
    {
        printf("%ld", (code >> (length - 1 - i)) & 0x1);
    }
    puts("");
}
int isZero(dwrd input)
{
    return (input | 0x7fffffff) == 0;
}
int isPositiveInfinity(dwrd input)
{
    return ((input >> 31) & 1) == 0 && (((input >> 23) & 0xff) == 255) && ((input & 0x7fffff) == 0);
}
int isNegativeInfiity(dwrd input)
{
    return ((input >> 31) & 1) == 1 && (((input >> 23) & 0xff) == 255) && ((input & 0x7fffff) == 0);
}
int isNan(dwrd input)
{
    return (((input >> 23) & 0xff) == 255) && ((input & 0x7fffff) != 0);
}
dwrd fadd(dwrd input1, dwrd input2)
{
    int exp1, exp2;
    exp1 = (input1 >> 23) & 0xFF;
    exp2 = (input2 >> 23) & 0xFF;
    dwrd tail1, tail2;
    // 获取尾数，添加前导0
    tail1 = (input1 & 0x7FFFFF) | 0x800000;
    tail2 = (input2 & 0x7FFFFF) | 0x800000;
    int opposite = 0;
    if (((((input1 >> 31) & 0x1) == 1) && ((input2 >> 31) & 0x1) == 0) || ((((input1 >> 31) & 0x1) == 0) && ((input2 >> 31) & 0x1) == 1))
        opposite = 1;
    if (exp1 >= exp2)
    {
        // 小的向大的对齐,对阶
        tail2 >>= (exp1 - exp2);
        if (opposite)
        {
            tail1 -= tail2;
            while ((tail1 & 0x800000) == 0)
            {
                tail1 <<= 1;
                exp1--;
            }
        }
        else
        {
            tail1 += tail2;
            while (tail1 & 0xFF000000)
            {
                tail1 >>= 1;
                exp1++;
            }
        }
        return (input1 & 0x80000000) | (exp1 << 23) | (tail1 & 0x7FFFFF);
    }
    else
    {
        // 对齐
        tail1 >>= (exp2 - exp1);
        if (opposite)
        {
            tail2 -= tail1;
            while ((tail2 & 0x800000) == 0)
            {
                tail2 <<= 1;
                exp2--;
            }
        }
        else
        {
            tail2 += tail1;
            while (tail2 & 0xFF000000)
            {
                tail2 >>= 1;
                exp2++;
            }
        }
        return (input2 & 0x80000000) | (exp2 << 23) | (tail2 & 0x7FFFFF);
    }
}
dwrd fsub(dwrd input1, dwrd input2)
{
    // printCode(input2, 32);
    if (((input2 >> 31) & 0x1) == 0)
    {
        input2 |= 0x80000000;
    }
    else
    {
        input2 &= 0x7fffffff;
    }
    // printCode(input2, 32);
    return fadd(input1, input2);
}
dwrd fmul(dwrd input1, dwrd input2)
{
    int exp1, exp2;
    dwrd tail1, tail2, tailResult = 0;
    exp1 = (input1 >> 23) & 0xFF;
    exp2 = (input2 >> 23) & 0xFF;
    //添加前导0
    tail1 = (input1 & 0x7FFFFF) | 0x800000;
    tail2 = (input2 & 0x7FFFFF) | 0x800000;
    int opposite = 0;
    if (((((input1 >> 31) & 0x1) == 1) && ((input2 >> 31) & 0x1) == 0) || ((((input1 >> 31) & 0x1) == 0) && ((input2 >> 31) & 0x1) == 1))
        opposite = 1;
    //避免重复加bias
    int expResult = exp1 + exp2 - 127;
    while (tail2 != 0)
    {
        // 模拟竖式运算
        tailResult >>= 1;
        if (tail2 & 1)
            tailResult += tail1;
        tail2 >>= 1;
        // printCode(tail2, 23);
        // printf("tailResult: %d\n", tailResult);
    }
    // 处理溢出
    while (tailResult & 0xFF000000)
    {
        tailResult >>= 1;
        expResult++;
    }
    expResult <<= 23;
    opposite <<= 31;
    tailResult &= 0x7FFFFF;
    dwrd result = opposite | expResult | tailResult;
    return result;
}

dwrd fdiv(dwrd input1, dwrd input2)
{
    if (isZero(input2))
    {
        return 0;
    }
    int opposite = 0;
    if (((((input1 >> 31) & 0x1) == 1) && ((input2 >> 31) & 0x1) == 0) || ((((input1 >> 31) & 0x1) == 0) && ((input2 >> 31) & 0x1) == 1))
        opposite = 1;
    int exp1, exp2, tail1, tail2, tailResult = 0, remain;
    exp1 = (input1 >> 23) & 0xFF;
    exp2 = (input2 >> 23) & 0xFF;
    tail1 = (input1 & 0x7FFFFF) | 0x00800000;
    tail2 = (input2 & 0x7FFFFF) | 0x00800000;
    int expResult = exp1 - exp2 + 127;
    remain = tail1;
    for (int i = 0; i < 24; i++)
    {
        // 模拟竖式除法
        int canSub = 0;
        if (remain > tail2)
        {
            remain -= tail2;
            canSub = 1;
        }
        remain <<= 1;
        tailResult = (tailResult << 1) | canSub;
    }
    // 处理溢出
    while ((tailResult & 0x00800000) == 0)
    {
        tailResult <<= 1;
        expResult--;
    }
    expResult <<= 23;
    opposite <<= 31;
    tailResult &= 0x7FFFFF;
    dwrd result = opposite | expResult | tailResult;
    return result;
}
//浮点转整数
long ftoi(dwrd input)
{
    // printf("%lu", input);
    int sign, exp, tail;
    sign = input & (0x80000000);
    exp = ((input & (0x7f800000)) >> 23) - 127;
    tail = (input & 0x7fffff);
    if (exp <= 0)
        return 0;
    long result = 1;
    int count = 1;
    // puts("");
    // for (int i = 23; i >= 0; i--)
    // {
    //     printf("%d", (tail >> i) & 0x1);
    // }
    // puts("");
    while (exp)
    {
        // printf("exp: %d, count%d: result: %ld\n", exp, count, result);
        exp -= 1;
        result = (result << 1) | (((tail >> (23 - count))) & 0x1);
        count++;

        // printf("exp: %d, count%d: result: %ld\n", exp, count, result);
    }
    return sign ? (~result) + 1 : result;
}
#define abs(x) ((x) >= 0 ? (x) : (-(x)))
#define min(a, b) ((a) < (b) ? (a) : (b))
//整数转浮点
dwrd itof(int number)
{
    // 如果sign是1，那么表示是负数，否则是正数
    int sign, exp, tail = 0;
    if (number == 0)
        return 0;
    sign = number < 0 ? 1 : 0;
    sign <<= 31;
    dwrd result = 0;
    number = abs(number);
    // printf("number: %d\n", number);
    int count = 0;
    while (number >> (count))
        count++;
    count--;
    // printf("%d", count);
    exp = (count + 127) << 23;
    number ^= (1 << count);
    // printf("count: %d\n", count);
    // printf("min : %d", min(23, count));
    // tail |= (number << (22 - count + 1));
    for (int i = 0; i < min(23, count); i++)
    {
        tail |= (((number >> (count - i - 1)) & 0x1) << (22 - i));
        // printf("round %d\ntemp : %d\n", i, ((number >> (count - i - 1)) & 0x1));
        // printCode(tail, 23);
        // printf("number: %d\n", number);
    }
    // printf("count : %d\ntailEnd: %d\n", count, tail & 0x1);
    if ((count > 22 && (tail & 0x1) == 0))
    {
        if ((number >> (count - 24)) & 0x1)
        {
            tail |= 1;
        }
    }
    result = sign | exp | (tail);

    return result;
}
int main()
{
    int choice = 0;
    while (1)
    {
        fflush(stdin);
        printf("输入进行的操作类型\n\t1:浮点转整数\n\t2:整数转浮点\n\t3:浮点加法\n\t4:浮点减法\n\t5:浮点乘法\n\t6:浮点除法\n\t7:退出\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("输入进行转换的浮点数\n");
            scanf("%f", &u.f);
            long result = ftoi(u.d);
            printf("结果：%d\n", result);
            break;
        }
        case 2:
        {
            printf("输入进行转换的整数\n");
            int temp;
            scanf("%d", &temp);
            u.d = itof(temp);
            printf("结果：%f\n", u.f);
            break;
        }
        case 3:
        {
            printf("输入进行加法的两个浮点数\n");
            scanf("%f %f", &u.f, &v.f);
            w.d = fadd(u.d, v.d);
            z.f = u.f + v.f;
            printf("%f + %f = %f\n", u.f, v.f, w.f);
            printf("%08lX -=> %08lX\n", w.d, z.d);
            break;
        }
        case 4:
        {
            printf("输入进行减法的两个浮点数\n");
            scanf("%f %f", &u.f, &v.f);
            w.d = fsub(u.d, v.d);
            z.f = u.f - v.f;
            printf("%f + %f = %f\n", u.f, v.f, w.f);
            printf("%08lX -=> %08lX\n", w.d, z.d);
            break;
        }
        case 5:
        {
            printf("输入进行乘法的两个浮点数\n");
            scanf("%f %f", &u.f, &v.f);
            w.d = fmul(u.d, v.d);
            z.f = u.f * v.f;
            printf("%f + %f = %f\n", u.f, v.f, w.f);
            printf("%08lX -=> %08lX\n", w.d, z.d);
            break;
        }
        case 6:
        {
            printf("输入进行除法的两个浮点数\n");
            scanf("%f %f", &u.f, &v.f);
            w.d = fdiv(u.d, v.d);
            z.f = u.f / v.f;
            printf("%f + %f = %f\n", u.f, v.f, w.f);
            printf("%08lX -=> %08lX\n", w.d, z.d);
            break;
        }
        case 7:
        {
            return 0;
        }
        }
    }
    return 0;
}

// 0000000101100011001100110011001
// 0000000001100011001100110011001