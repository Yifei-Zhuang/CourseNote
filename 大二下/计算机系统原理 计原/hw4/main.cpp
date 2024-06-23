#include "assemble.cpp"
#include "disAssembler.cpp"

using namespace std;
Assembler assembler;
DisAssembler disAssembler;
int PC = 0;
void viewMemoryInStruction(int startPos, int limits)
{
    if (startPos < 0)
    {
        cerr << "start Pos cannot be negative\n"
             << endl;
        return;
    }
    if (startPos + limits >= ((uint64_t(1) << 32) - 1))
    {
        cerr << "memory overflow!\n"
             << endl;
        return;
    }
    for (int i = startPos; i < startPos + limits; i++)
    {
        cout << left << intToHex(i) + ":" + disAssembler.disAssemble(memory[i]);
        puts("");
    }
    puts("");
}
void writeToMemory(int memPos = 0, string ins = "SLL $zero,$zero,0")
{
    if (memPos < 0 || memPos >= (uint64_t(1) << 32) - 1)
    {
        cerr << "invalid memory address";
        return;
    }
    memory[memPos] = assembler.Assemble(ins);
}
void writeToMemory(int memPos = 0, uint32_t ins = 0)
{
    if (memPos < 0 || memPos >= (uint64_t(1) << 32) - 1)
    {
        cerr << "invalid memory address\n";
        return;
    }
    memory[memPos] = ins;
}
void executeInstruction(uint32_t mempos)
{
    PC++;
    if (mempos < 0)
    {
        cerr << "memory address cannot be negative\n";
        return;
    }
    uint32_t operationCode = memory[mempos];
    uint32_t instr = (operationCode >> 26) & 0x03f;
    int rs = (operationCode >> 21) & 0x1f;
    int rt = (operationCode >> 16) & 0x1f;
    int rd = (operationCode >> 11) & 0x1f;
    int sa = (operationCode >> 6) & 0x1f;
    int fun = (operationCode)&0x3f;
    int dat = (operationCode)&0xffff;
    if (instr == 15)
    {
        // lui
        registers[rt] = (dat << 16);
        return;
    }
    else if (instr == 0x000000)
    {
        if (fun == 0x20)
        {
            registers[rd] = registers[rs] + registers[rt];
        }
        else if (fun == 0x22)
        {
            // SUB
            registers[rd] = registers[rs] - registers[rt];
        }
        else if (fun == 0x2A)
        {
            // SLT
            registers[rd] = registers[rs] < registers[rt] ? 1 : 0;
        }
        else if (fun == 0x2B)
        {
            // SLTu
            registers[rd] = (static_cast<uint64_t>(registers[rs]) < static_cast<uint64_t>(registers[rt])) ? 1 : 0;
        }
        else if (fun == 0x24)
        {
            // AND
            registers[rd] = registers[rs] & registers[rt];
        }
        else if (fun == 0x25)
        {
            // OR
            registers[rd] = registers[rs] | registers[rt];
        }
        else if (fun == 0x26)
        {
            // XOR
            registers[rd] = registers[rs] ^ registers[rt];
        }
        else if (fun == 0x26)
        {
            // XOR
            registers[rd] = registers[rs] ^ registers[rt];
        }
        else if (fun == 0x27)
        {
            // NOR
            registers[rd] = ~(registers[rs] | registers[rt]);
        }
        else if (fun == 0)
        {
            // SLL
            registers[rd] = registers[rs] << sa;
        }
        else if (fun == 4)
        {
            // SLLv
            registers[rd] = registers[rs] << registers[rt];
        }
        else if (fun == 2)
        {
            // SRL
            int temp = registers[rs];
            if (temp < 0)
                temp &= ((uint64_t(1) << 31) - 1);
            registers[rd] = temp >> registers[sa];
        }
        else if (fun == 6)
        {
            // SRLv
            registers[rd] = registers[rs] >> registers[sa];
        }
        else if (fun == 3)
        {
            // SRA
            int flag = registers[rs] < 0 ? 1 : 0;
            registers[rd] = registers[rs];
            for (int i = 0; i < sa; i++)
            {
                registers[rd] >>= 1;
                registers[rd] |= (flag << 31);
            }
        }
        else if (fun == 7)
        {
            // SRAv
            registers[rd] = registers[rs] >> registers[rt];
        }
        else if (fun == 8)
        {
            // JR
            PC = registers[rs];
        }
        else if (fun == 9)
        {
            // JALr
            registers[rd] = PC;
            PC = registers[rs];
        }
        return;
    }
    else if (instr == 0x001000)
    {
        // ADDi
        registers[rt] = registers[rs] + dat;
    }
    else if (instr == 10)
    {
        // SLTi
        registers[rt] = registers[rs] < dat ? 1 : 0;
    }
    else if (instr == 11)
    {
        // SLTiu
        registers[rt] = static_cast<uint64_t>(registers[rs]) < static_cast<uint64_t>(registers[dat]) ? 1 : 0;
    }
    else if (instr == 12)
    {
        // ANDi
        registers[rt] = registers[rd] & dat;
    }
    else if (instr == 13)
    {
        // ORi
        registers[rt] = registers[rs] | dat;
    }
    else if (instr == 14)
    {
        // XORi
        registers[rt] = registers[rd] ^ dat;
    }
    else if (instr == 35)
    {
        // LW
        registers[rt] = memory[registers[rs] + dat];
    }
    else if (instr == 43)
    {
        // SW
        // memory[registers[rs] + dat] = registers[rt];
    }
    else if (instr == 4)
    {
        // BEQ
        if (registers[rs] == registers[rt])
            PC += dat;
    }
    else if (instr == 5)
    {
        // BNE
        if (registers[rs] != registers[rt])
            PC += dat;
    }
    else if (instr == 1)
    {
        // BGEZAL
        if (registers[rs] >= 0)
        {
            registers[31] = PC;
            PC += dat;
        }
    }
    else if (instr == 2)
    {
        // J
        PC = (PC & 0xF8000000) | dat;
    }
    else if (instr == 3)
    {
        // JAL
        registers[31] = PC;
        PC = (PC & 0xF8000000) + dat;
    }
}
int main()
{
    init();
    string input;
    cout << "初始化完成!" << endl;
    cout << "欢迎使用简陋版mips模拟器,可用指令为:\n"
         << "\tR: 看寄存器\n"
         << "\tD: 数据方式看内存\n"
         << "\tU: 指令方式看内存\n"
         << "\tA: 写汇编指令到内存\n"
         << "\tT: 单步执行内存中的指令\n";

    while (true)
    {
        getline(cin, input);
        trim(input);
        if (input.empty() || input.size() > 1)
        {
            cout << "指令只能是 R, D, U, A, T\n";
            continue;
        }
        switch (::toupper(input[0]))
        {
        case 'R':
        {
            showAllRegisters();
            break;
        }
        case 'D':
        {
            int startpos = 0;
            int limits = 100;
            cout << "输入内存的起始位置和想要看的内存地址的个数,起始位置用16进制表示\n";
            cin >> hex >> startpos;
            cin >> limits;
            showMemory(startpos, limits);
            fflush(stdin);
            break;
        }
        case 'U':
        {
            int startpos = 0;
            int limits = 100;
            cout << "输入内存的起始位置和想要看的内存地址的个数,起始位置16进制表示\n";
            cin >> hex >> startpos;
            cin >> limits;
            viewMemoryInStruction(startpos, limits);
            getchar();
            break;
        }
        case 'A':
        {
            int mempos = 0;
            string input = "";
            cout << "输入要修改的内存位置和相应的指令,内存位置用16进制表示\n";
            cin >> hex >> mempos;
            if (cin.peek() == '\n')
                getchar();
            getline(cin, input);
            trim(input);
            if (input.size() > 2 && input[0] == '0' && (input[1] == 'X' || input[1] == 'x'))
            {
                writeToMemory(mempos, string_to_bit(input));
            }
            else
            {
                writeToMemory(mempos, input);
            }
            break;
        }
        case 'T':
        {
            executeInstruction(PC);
            break;
        }
        default:
        {
            cout << "指令只能是 R, D, U, A, T\n";
        }
        }
    }
    return 0;
}