#include <iostream>
#include <string.h>
#include <bitset>
#include <iomanip>
using namespace std;
typedef unsigned int word;
bool hasOverflow = false;
uint16_t __8To16(uint8_t input)
{
    uint16_t res = 0;
    for (int i = 0; i < 8; i++)
        res |= (input & (1 << i));
    for (int i = 8; i < 16; i++)
    {
        res |= ((input >> 7) << i);
    }
    return res;
}
uint32_t __16To32(uint16_t input)
{
    uint32_t res = 0;
    for (int i = 0; i < 16; i++)
        res |= (input & (1 << i));
    for (int i = 16; i < 32; i++)
    {
        res |= ((input >> 15) << i);
    }
    return res;
}
int compare(word a, word b)
{
    if ((((a >> 31) & 1) == 1) && !(((b >> 31) & 1) == 1))
        return -1;
    else if (!(((a >> 31) & 1) == 1) && (((b >> 31) & 1) == 1))
        return 1;
    else
    {
        for (int i = 30; i >= 0; i--)
        {
            int temp = ((a >> i) & 1) - ((b >> i) & 1);
            if (temp == -1)
                return -1;
            else if (temp == 1)
                return 1;
        }
    }
    return 0;
}
//字符串转换成对应的二进制
// 输入： -8, 输出0xfffffff0
word atom(const char *input)
{
    return static_cast<word>(strtol(input, NULL, 10));
}
char *mtoa(word input)
{
    auto temp = bitset<32>(input);
    char *res = new char[33];
    for (int i = 0; i < 32; i++)
    {
        res[i] = temp.test(31 - i) ? '1' : '0';
    }
    res[32] = '\0';
    return res;
}
word madd(word a, word b)
{
    if (b == 0)
        return a;
    else
    {
        word res = madd(a ^ b, (a & b) << 1);
        if ((compare(res, 0) == 1 && compare(a, 0) == -1 && compare(b, 0) == -1) || (compare(res, 0) == -1 && compare(a, 0) == 1 && compare(b, 0) == 1))
            hasOverflow = true;

        // cout << " compare res " << res << " and 0 : " << compare(res, 0) << endl;

        // cout << " compare a " << a << " and 0 : " << compare(a, 0) << endl;

        // cout << " compare b" << b << " and 0 : " << compare(b, 0) << endl;

        return res;
    }
}
word msub(word a, word b)
{
    return madd(a, madd(~b, 1));
}
word mmul(word a, word b)
{
    int res = 0;
    for (int i = 0; i <= 31; i++)
    {
        if ((b >> i) & 1)
        {
            res = madd(res, a);
        }
        a <<= 1;
    }
    if ((compare(res, 0) == 1 && compare(a, 0) == -1 && compare(b, 0) == -1) || (compare(res, 0) == -1 && compare(a, 0) == 1 && compare(b, 0) == 1))
        hasOverflow = true;
    return res;
}
word mdiv(word a, word b)
{
    bool sign = 0;
    if (((a >> 31) & 1) ^ ((b >> 31) & 1))
        sign = 1;
    if ((int)a < 0)
        a = madd(~a, 1);
    if ((int)b < 0)
        b = madd(~b, 1);
    if (compare(a, b) == -1)
    {
        return 0;
    }
    int res = 0;
    while (compare(a, b) > 0)
    {
        res = madd(res, 1);
        a = msub(a, b);
    }
    return sign ? -res : res;
}
word mmod(word a, word b)
{
    auto temp = msub(a, mmul(b, mdiv(a, b)));
    if (static_cast<int>(temp) < 0)
        temp = madd(temp, b);
    return temp;
}
int main()
{
    string temp = "-100";
    auto res = atom(temp.c_str());
    cout << endl
         << setw(30) << left
         << "string to binary : "
         << mtoa(res);
    cout << endl
         << setw(30) << left
         << "add 1 and 10000 : "
         << (madd(1, 10000));
    cout << endl
         << setw(30) << left
         << "add 2147483647 and 1 : "
         << static_cast<word>(madd(2147483647, 1))
         << (hasOverflow
                 ? " overflow!"
                 : "no overflow");

    cout << endl
         << setw(30) << left
         << "subtract 1 and 10000 : "
         << static_cast<int>((msub(1, 10000)));
    cout << endl
         << setw(30) << left
         << "mul 10 and 20000 : "
         << ((mmul(10, 20000)));

    cout << endl
         << setw(30) << left
         << "div -10000 and 3 : "
         << static_cast<int>(mdiv(-10000, 3));

    cout << endl
         << setw(30) << left
         << "10000 mod 3 : "
         << static_cast<int>(mmod(10000, 3));

    cout << endl
         << setw(30) << left
         << "8 bit to 16 bit : "
         << mtoa(__8To16(static_cast<uint8_t>(-7)));

    cout << endl
         << setw(30) << left
         << "16 bit to 32 bit :"
         << mtoa(__16To32(static_cast<uint16_t>(-10)));
}