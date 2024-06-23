#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
void output(ofstream &of, FILE *hzkfp, unsigned char word[])
{
    int i, j, k, offset;
    int flag;
    unsigned char key[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char buffer[32];
    offset = (94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;
    fseek(hzkfp, offset, SEEK_SET);
    fread(buffer, 1, 32, hzkfp);
    char temp[2];
    for (k = 0; k < 16; k++)
    {
        for (j = 0; j < 2; j++)
        {
            for (i = 0; i < 8; i++)
            {
                flag = buffer[k * 2 + j] & key[i];
                for (int i = 0; i < 2; i++)
                    sprintf(temp, "%s", flag ? "#" : "-");
                of << temp[0];
            }
        }
        of << "\n";
    }
    of << ("========================================\n");
}
void biggerOutput(ofstream &of, FILE *hzkfp, unsigned char word[], int times)
{
    int i, j, k, offset;
    int flag;
    unsigned char key[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char buffer[32];
    offset = (94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;
    fseek(hzkfp, offset, SEEK_SET);
    char temp[2];
    fread(buffer, 1, 32, hzkfp);
    for (k = 0; k < 16; k++)
    {
        for (j = 0; j < 2; j++)
        {
            for (i = 0; i < 8; i++)
            {
                flag = buffer[k * 2 + j] & key[i];
                for (int i = 0; i < 2 * times; i++)
                {
                    sprintf(temp, "%s", flag ? "#" : "-");
                    of << temp[0];
                }
            }
        }
        of << "\n";
    }
    of << ("========================================\n");
}
void italicOutput(ofstream &of, FILE *hzkfp, unsigned char word[])
{
    int i, j, k, offset;
    int flag;
    unsigned char key[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char buffer[32];
    offset = (94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;
    fseek(hzkfp, offset, SEEK_SET);
    char temp[2];
    fread(buffer, 1, 32, hzkfp);
    for (k = 0; k < 16; k++)
    {
        for (int i = 0; i < 32 - k; i++)
            of << "-";
        for (j = 0; j < 2; j++)
        {

            for (i = 0; i < 8; i++)
            {
                flag = buffer[k * 2 + j] & key[i];
                for (int i = 0; i < 2; i++)
                {
                    sprintf(temp, "%s", flag ? "#" : "-");
                    of << temp[0];
                }
            }
        }
        for (int i = 0; i < k; i++)
            of << "-";
        of << "\n";
    }
    of << ("========================================\n");
}
void handstandOutput(ofstream &of, FILE *hzkfp, unsigned char word[])
{
    int i, j, k, offset;
    int flag;
    unsigned char key[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char buffer[32];
    offset = (94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;
    fseek(hzkfp, offset, SEEK_SET);
    char temp[2];
    fread(buffer, 1, 32, hzkfp);
    for (k = 16; k > 0; k--)
    {
        for (j = 2; j > 0; j--)
        {

            for (i = 0; i < 8; i++)
            {
                flag = buffer[k * 2 + j] & key[i];
                for (int i = 0; i < 2; i++)
                {
                    sprintf(temp, "%s", flag ? "#" : "-");
                    of << temp[0];
                }
            }
        }
        of << "\n";
    }
    of << ("========================================\n");
}
void colorOutput(FILE *hzkfp, unsigned char word[])
{

    int i, j, k, offset;
    int flag;
    unsigned char key[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char buffer[32];
    offset = (94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;
    fseek(hzkfp, offset, SEEK_SET);
    fread(buffer, 1, 32, hzkfp);
    char temp[2];
    for (k = 0; k < 16; k++)
    {
        for (j = 0; j < 2; j++)
        {
            for (i = 0; i < 8; i++)
            {
                flag = buffer[k * 2 + j] & key[i];
                for (int i = 0; i < 2; i++)
                    sprintf(temp, "%s", flag ? "#" : "-");
                cout << "\033[35m" << temp[0];
            }
        }
        cout << "\n";
    }
    cout << ("========================================\n");
    cout << "\033[0m";
}
void kongxinOutput(ofstream &of, FILE *hzkfp, unsigned char word[])
{

    int i, j, k, offset;
    int flag;
    unsigned char key[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char buffer[32];
    offset = (94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;
    fseek(hzkfp, offset, SEEK_SET);
    fread(buffer, 1, 32, hzkfp);
    char temp[2];
    for (k = 0; k < 16; k++)
    {
        for (j = 0; j < 2; j++)
        {
            for (i = 0; i < 8; i++)
            {
                flag = buffer[k * 2 + j] & key[i];
                if (flag)
                {
                    of << "#";
                }
                else
                {
                    of << " ";
                }
            }
        }
        of << "\n";
    }
    of << ("========================================\n");
}
int main(void)
{
    FILE *hzkfp = NULL;
    ofstream of("output.txt", ios::out);
    ofstream biggerOf("biggerOutput.txt", ios::out);
    ofstream italicOf("italicOutput.txt", ios::out);
    ofstream handstandOf("handstandOutput.txt", ios::out);
    ofstream kongxinOf("kongxinOutput.txt", ios::out);

    hzkfp = fopen("hzk16", "rb");
    if (hzkfp == NULL)
    {
        fprintf(stderr, "error hzk16\n");
        return 1;
    }
    ifstream bif;
    bif.open("b.txt", ios::binary | ios::in);

    unsigned char word[2]; // 改成你的转码后的汉字编码
    bif.seekg(0, ios::end);
    int number = static_cast<int>(bif.tellg()) - 1;
    bif.seekg(0, ios::beg);
    int times = 0;
    cout << "原样输出\n";
    for (int i = 0; i < number / 2; i++)
    {
        bif.read((char *)(&word), 2);
        output(of, hzkfp, word);
    }
    cout << "原样输出结束\n";
    bif.seekg(0, ios::beg);
    cout << "放大输出，请输入放大倍数\n";
    cin >> times;
    for (int i = 0; i < number / 2; i++)
    {
        bif.read((char *)(&word), 2);
        biggerOutput(biggerOf, hzkfp, word, times);
    }
    cout << "放大输出结束\n";
    bif.seekg(0, ios::beg);
    cout << "斜体输出\n";
    for (int i = 0; i < number / 2; i++)
    {
        bif.read((char *)(&word), 2);
        italicOutput(italicOf, hzkfp, word);
    }
    cout << "斜体输出结束\n";
    bif.seekg(0, ios::beg);
    cout << "倒立输出\n";
    for (int i = 0; i < number / 2; i++)
    {
        bif.read((char *)(&word), 2);
        handstandOutput(handstandOf, hzkfp, word);
    }
    cout << "倒立输出结束\n";
    bif.seekg(0, ios::beg);
    cout << "彩色输出\n";
    for (int i = 0; i < number / 2; i++)
    {
        bif.read((char *)(&word), 2);
        colorOutput(hzkfp, word);
    }
    cout << "彩色输出结束\n";
    bif.seekg(0, ios::beg);
    cout << "空心输出\n";
    for (int i = 0; i < number / 2; i++)
    {
        bif.read((char *)(&word), 2);
        kongxinOutput(kongxinOf, hzkfp, word);
    }
    cout << "空心输出结束\n";
    fclose(hzkfp);
    return 0;
}
