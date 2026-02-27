#include "processor.hxx"

Processor::Processor(Memory &mem) : mem(mem)
{
    this->PopulateInstructionMap();
}

Processor::~Processor()
{
}

bool Processor::NextCycle()
{
    if (reg.cycles_remaining != 0)
    {
        reg.cycles_remaining--;
        /// TODO Add delay timer to simulate machine cycle :)
        return true;
    }
    else
    {
        return NextInstruction();
    }
}

bool Processor::NextInstruction()
{
    bool should_proceed = mem.PeekByte(reg.pc) != 0x00;
    Instruction(this->instructions[mem.PeekByte(reg.pc)])(mem, reg, alu);
    return should_proceed;
}

void Processor::ResetProcessor()
{
    this->reg = Registers();
    this->mem.ResetMemory();
    this->alu.ResetALU();
    return;
}

void Processor::OperationUndefined(Memory &mem, Registers &reg, ALU &alu)
{
    byte illegal_opcode = mem.PeekByte(reg.pc);
    std::cout
        << std::format(
               "Illegal opcode {:02X} at {:04X}",
               illegal_opcode, reg.pc)
        << std::endl;
}

void Processor::PopulateInstructionMap()
{
    this->instructions[0x00] = Operation00;
    this->instructions[0x01] = Operation01;
    this->instructions[0x05] = Operation05;
    this->instructions[0x06] = Operation06;
    this->instructions[0x08] = Operation08;
    this->instructions[0x09] = Operation09;
    this->instructions[0x0A] = Operation0A;
    this->instructions[0x0D] = Operation0D;
    this->instructions[0x0E] = Operation0E;
    this->instructions[0x10] = Operation10;
    this->instructions[0x11] = Operation11;
    this->instructions[0x15] = Operation15;
    this->instructions[0x16] = Operation16;
    this->instructions[0x18] = Operation18;
    this->instructions[0x19] = Operation19;
    this->instructions[0x1D] = Operation1D;
    this->instructions[0x1E] = Operation1E;
    this->instructions[0x20] = Operation20;
    this->instructions[0x21] = Operation21;
    this->instructions[0x24] = Operation24;
    this->instructions[0x25] = Operation25;
    this->instructions[0x26] = Operation26;
    this->instructions[0x28] = Operation28;
    this->instructions[0x29] = Operation29;
    this->instructions[0x2A] = Operation2A;
    this->instructions[0x2C] = Operation2C;
    this->instructions[0x2D] = Operation2D;
    this->instructions[0x2E] = Operation2E;
    this->instructions[0x30] = Operation30;
    this->instructions[0x31] = Operation31;
    this->instructions[0x35] = Operation35;
    this->instructions[0x36] = Operation36;
    this->instructions[0x38] = Operation38;
    this->instructions[0x39] = Operation39;
    this->instructions[0x3D] = Operation3D;
    this->instructions[0x3E] = Operation3E;
    this->instructions[0x40] = Operation40;
    this->instructions[0x41] = Operation41;
    this->instructions[0x45] = Operation45;
    this->instructions[0x46] = Operation46;
    this->instructions[0x48] = Operation48;
    this->instructions[0x49] = Operation49;
    this->instructions[0x4A] = Operation4A;
    this->instructions[0x4C] = Operation4C;
    this->instructions[0x4D] = Operation4D;
    this->instructions[0x4E] = Operation4E;
    this->instructions[0x50] = Operation50;
    this->instructions[0x51] = Operation51;
    this->instructions[0x55] = Operation55;
    this->instructions[0x56] = Operation56;
    this->instructions[0x58] = Operation58;
    this->instructions[0x59] = Operation59;
    this->instructions[0x5D] = Operation5D;
    this->instructions[0x5E] = Operation5E;
    this->instructions[0x60] = Operation60;
    this->instructions[0x61] = Operation61;
    this->instructions[0x65] = Operation65;
    this->instructions[0x66] = Operation66;
    this->instructions[0x68] = Operation68;
    this->instructions[0x69] = Operation69;
    this->instructions[0x6A] = Operation6A;
    this->instructions[0x6C] = Operation6C;
    this->instructions[0x6D] = Operation6D;
    this->instructions[0x6E] = Operation6E;
    this->instructions[0x70] = Operation70;
    this->instructions[0x71] = Operation71;
    this->instructions[0x75] = Operation75;
    this->instructions[0x76] = Operation76;
    this->instructions[0x78] = Operation78;
    this->instructions[0x79] = Operation79;
    this->instructions[0x7D] = Operation7D;
    this->instructions[0x7E] = Operation7E;
    this->instructions[0x81] = Operation81;
    this->instructions[0x84] = Operation84;
    this->instructions[0x85] = Operation85;
    this->instructions[0x86] = Operation86;
    this->instructions[0x88] = Operation88;
    this->instructions[0x8A] = Operation8A;
    this->instructions[0x8C] = Operation8C;
    this->instructions[0x8D] = Operation8D;
    this->instructions[0x8E] = Operation8E;
    this->instructions[0x90] = Operation90;
    this->instructions[0x91] = Operation91;
    this->instructions[0x94] = Operation94;
    this->instructions[0x95] = Operation95;
    this->instructions[0x96] = Operation96;
    this->instructions[0x98] = Operation98;
    this->instructions[0x99] = Operation99;
    this->instructions[0x9A] = Operation9A;
    this->instructions[0x9D] = Operation9D;
    this->instructions[0xA0] = OperationA0;
    this->instructions[0xA1] = OperationA1;
    this->instructions[0xA2] = OperationA2;
    this->instructions[0xA4] = OperationA4;
    this->instructions[0xA5] = OperationA5;
    this->instructions[0xA6] = OperationA6;
    this->instructions[0xA8] = OperationA8;
    this->instructions[0xA9] = OperationA9;
    this->instructions[0xAA] = OperationAA;
    this->instructions[0xAC] = OperationAC;
    this->instructions[0xAD] = OperationAD;
    this->instructions[0xAE] = OperationAE;
    this->instructions[0xB0] = OperationB0;
    this->instructions[0xB1] = OperationB1;
    this->instructions[0xB4] = OperationB4;
    this->instructions[0xB5] = OperationB5;
    this->instructions[0xB6] = OperationB6;
    this->instructions[0xB8] = OperationB8;
    this->instructions[0xB9] = OperationB9;
    this->instructions[0xBA] = OperationBA;
    this->instructions[0xBC] = OperationBC;
    this->instructions[0xBD] = OperationBD;
    this->instructions[0xBE] = OperationBE;
    this->instructions[0xC0] = OperationC0;
    this->instructions[0xC1] = OperationC1;
    this->instructions[0xC4] = OperationC4;
    this->instructions[0xC5] = OperationC5;
    this->instructions[0xC6] = OperationC6;
    this->instructions[0xC8] = OperationC8;
    this->instructions[0xC9] = OperationC9;
    this->instructions[0xCA] = OperationCA;
    this->instructions[0xCC] = OperationCC;
    this->instructions[0xCD] = OperationCD;
    this->instructions[0xCE] = OperationCE;
    this->instructions[0xD0] = OperationD0;
    this->instructions[0xD1] = OperationD1;
    this->instructions[0xD5] = OperationD5;
    this->instructions[0xD6] = OperationD6;
    this->instructions[0xD8] = OperationD8;
    this->instructions[0xD9] = OperationD9;
    this->instructions[0xDD] = OperationDD;
    this->instructions[0xDE] = OperationDE;
    this->instructions[0xE0] = OperationE0;
    this->instructions[0xE1] = OperationE1;
    this->instructions[0xE4] = OperationE4;
    this->instructions[0xE5] = OperationE5;
    this->instructions[0xE6] = OperationE6;
    this->instructions[0xE8] = OperationE8;
    this->instructions[0xE9] = OperationE9;
    this->instructions[0xEA] = OperationEA;
    this->instructions[0xEC] = OperationEC;
    this->instructions[0xED] = OperationED;
    this->instructions[0xEE] = OperationEE;
    this->instructions[0xF0] = OperationF0;
    this->instructions[0xF1] = OperationF1;
    this->instructions[0xF5] = OperationF5;
    this->instructions[0xF6] = OperationF6;
    this->instructions[0xF8] = OperationF8;
    this->instructions[0xF9] = OperationF9;
    this->instructions[0xFD] = OperationFD;
    this->instructions[0xFE] = OperationFE;

    for (auto &i : this->instructions)
    {
        if (i == nullptr)
            i = this->OperationUndefined;
    }
}

void Processor::PushByte(Memory &mem, Registers &reg, const byte &value)
{
    mem.PutByte(reg.sp--, value);
    return;
}

void Processor::PushWord(Memory &mem, Registers &reg, const word &value)
{
    mem.PutByte(reg.sp--, byte(value & 0xff00));
    mem.PutByte(reg.sp--, byte(value & 0x00ff));
    return;
}

byte Processor::PullByte(Memory &mem, Registers &reg)
{
    return mem.PeekByte(--reg.sp);
}

word Processor::PullWord(Memory &mem, Registers &reg)
{
    word result = mem.PeekWord(--reg.sp);
    reg.sp--;
    return result;
}

byte Processor::GetOperandZP(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    byte offset = mem.PeekByte(head, 1);
    reg.last_addr = offset;
    return mem.PeekByte(offset + 0x0000);
}

byte Processor::GetOperandZPX(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    byte offset = mem.PeekByte(head, 1) + reg.xr;
    reg.last_addr = offset;
    return mem.PeekByte(offset + 0x0000);
}

byte Processor::GetOperandZPY(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    byte offset = mem.PeekByte(head, 1) + reg.yr;
    reg.last_addr = offset;
    return mem.PeekByte(offset + 0x0000);
}

byte Processor::GetOperandAbs(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    word addr = mem.PeekWord(head, 1);
    reg.last_addr = addr;
    return mem.PeekByte(addr);
}

byte Processor::GetOperandAbX(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    word addr = mem.PeekWord(head, 1) + reg.xr;
    reg.last_addr = addr;

    if ((addr & 0xff00) != (mem.PeekWord(head, 1) & 0xff00))
        reg.additional_cycle = true;

    return mem.PeekByte(addr);
}

byte Processor::GetOperandAbY(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    word addr = mem.PeekWord(head, 1) + reg.yr;
    reg.last_addr = addr;

    if ((addr & 0xff00) != (mem.PeekWord(head, 1) & 0xff00))
        reg.additional_cycle = true;

    return mem.PeekByte(addr);
}

word Processor::GetOperandInd(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    word addr = mem.PeekWord(head, 1);
    reg.last_addr = addr;
    return mem.PeekWord(addr);
}

byte Processor::GetOperandIdX(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    byte offset = mem.PeekByte(head, 1) + reg.xr;
    word addr = mem.PeekWord(offset + 0x0000);
    reg.last_addr = addr;
    return mem.PeekByte(addr);
}

byte Processor::GetOperandIdY(Memory &mem, Registers &reg, const word &head)
{
    reg.additional_cycle = false;
    word offset = mem.PeekByte(head, 1) + reg.yr;
    word addr = mem.PeekWord(offset + 0x0000);
    reg.last_addr = addr;

    if ((offset & 0xff00) != (mem.PeekByte(head, 1)))
        reg.additional_cycle = true;

    return mem.PeekByte(addr);
}

void Processor::Operation00(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BRK (Address mode: impl)
    byte opcode = 0x00;
    word int_vec = mem.PeekWord(0xfffe);

    PushWord(mem, reg, reg.pc + 2);
    PushByte(mem, reg, byte(reg.sr.to_ulong()) & FLAG_B);

    reg.pc = int_vec;
    reg.cycles_remaining = 7 - 1;

    return;
}

void Processor::Operation01(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ORA (Address mode: indx)
    byte opcode = 0x01;

    alu.ar = reg.ac;
    alu.br = GetOperandIdX(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_ORA);
    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation05(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ORA (Address mode: zpg)
    byte opcode = 0x05;

    alu.ar = reg.ac;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_ORA);
    reg.pc += 2;
    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::Operation06(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ASL (Address mode: zpg)
    byte opcode = 0x06;

    alu.ar = GetOperandZP(mem, reg, reg.pc);
    byte res = alu.DoShiftOrRotatioin(OP_ASL);
    mem.PutByte(reg.last_addr, res);

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1;

    return;
}

void Processor::Operation08(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics PHP (Address mode: impl)
    byte opcode = 0x08;

    byte sr = reg.sr.to_ulong() & FLAG_B & 0b00100000;
    PushByte(mem, reg, sr);

    reg.pc += 1;
    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::Operation09(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ORA (Address mode: #)
    byte opcode = 0x09;

    alu.ar = reg.ac;
    alu.br = mem.PeekByte(reg.pc, 1);
    reg.ac = alu.DoLogicalOperation(OP_ORA);

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1;
    return;
}

void Processor::Operation0A(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ASL (Address mode: A)
    byte opcode = 0x0A;

    alu.ar = reg.ac;
    reg.ac = alu.DoShiftOrRotatioin(OP_ASL);

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation0D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ORA (Address mode: abs)
    byte opcode = 0x0D;
    alu.ar = reg.ac;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoLogicalOperation(OP_ORA));

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation0E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ASL (Address mode: abs)
    byte opcode = 0x0E;
    alu.ar = GetOperandAbs(mem, reg, reg.pc);
    byte res = alu.DoShiftOrRotatioin(OP_ASL);

    mem.PutByte(reg.last_addr, res);

    reg.pc += 3;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation10(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BPL (Address mode: rel)
    byte opcode = 0x10;
    byte operand = mem.PeekByte(reg.pc, 1);
    byte cycle_offset = 0;
    byte org_pc = reg.pc;

    if (reg.sr[FLAG_N] == false)
    {
        cycle_offset += 1;
        if (operand > 128)
        {
            reg.pc -= (0xff - operand + 1);
        }
        else
        {
            reg.pc += operand;
        }
    }

    if ((org_pc & 0xff00) != (reg.pc & 0xff00))
        cycle_offset += 1;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + cycle_offset;

    return;
}

void Processor::Operation11(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ORA (Address mode: indy)
    byte opcode = 0x11;
    alu.ar = reg.ac;
    alu.br = GetOperandIdY(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_ORA);

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation15(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ORA (Address mode: zpgx)
    byte opcode = 0x15;
    alu.ar = reg.ac;
    alu.br = GetOperandZPX(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_ORA);

    reg.cycles_remaining = 4 - 1;
    reg.pc += 2;

    return;
}

void Processor::Operation16(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ASL (Address mode: zpgx)
    byte opcode = 0x16;
    alu.ar = GetOperandZPX(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ASL));

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation18(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CLC (Address mode: impl)
    byte opcode = 0x18;

    reg.sr[FLAG_C] = false;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation19(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ORA (Address mode: absy)
    byte opcode = 0x19;
    alu.ar = reg.ac;
    alu.br = GetOperandAbY(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_ORA);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation1D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ORA (Address mode: absx)
    byte opcode = 0x1D;
    alu.ar = reg.ac;
    alu.br = GetOperandAbX(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_ORA);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation1E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ASL (Address mode: absx)
    byte opcode = 0x1E;
    alu.ar = GetOperandAbX(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ASL));

    reg.pc += 3;
    reg.cycles_remaining = 7 - 1;

    return;
}

void Processor::Operation20(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics JSR (Address mode: abs)
    byte opcode = 0x20;
    word addr = reg.pc + 2;
    /// It seems that the address being pushed is [PC+2] not [PC+3].
    /// I guess it is so because RTS increments PC by 1 byte after
    /// it pulled [PC+2] and put it into PC.

    PushWord(mem, reg, addr);

    reg.pc = GetOperandAbs(mem, reg, reg.pc);
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation21(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics AND (Address mode: indx)
    byte opcode = 0x21;

    alu.ar = reg.ac;
    alu.br = GetOperandAbX(mem, reg, reg.pc);
    reg.ac = alu.DoLogicalOperation(OP_AND);

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation24(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BIT (Address mode: zpg)
    byte opcode = 0x24;
    alu.ar = reg.ac;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    alu.DoBITOperation();

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation25(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics AND (Address mode: zpg)
    byte opcode = 0x25;
    alu.ar = reg.ac;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_AND);

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation26(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROL (Address mode: zpg)
    byte opcode = 0x26;
    alu.ar = GetOperandZP(mem, reg, reg.pc);
    alu.DoShiftOrRotatioin(OP_ROL);

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation28(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics PLP (Address mode: impl)
    byte opcode = 0x28;
    byte res = PullByte(mem, reg);
    reg.sr = (res & 0b11001111) | (byte(reg.sr.to_ulong()) & 0b00110000);

    reg.pc += 1;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation29(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics AND (Address mode: #)
    byte opcode = 0x29;
    alu.ar = reg.ac;
    alu.br = mem.PeekByte(reg.pc, 1);

    reg.ac = alu.DoLogicalOperation(OP_AND);

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation2A(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROL (Address mode: A)
    byte opcode = 0x2A;
    alu.ar = reg.ac;
    reg.ac = alu.DoShiftOrRotatioin(OP_ROL);

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation2C(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BIT (Address mode: abs)
    byte opcode = 0x2C;
    alu.ar = reg.ac;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    alu.DoBITOperation();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation2D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics AND (Address mode: abs)
    byte opcode = 0x2D;
    alu.ar = reg.ac;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_AND);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation2E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROL (Address mode: abs)
    byte opcode = 0x2E;

    alu.ar = GetOperandAbs(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ROL));

    reg.pc += 3;
    reg.cycles_remaining = 6 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation30(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BMI (Address mode: rel)
    byte opcode = 0x30;
    byte operand = mem.PeekByte(reg.pc, 1);
    byte cycle_offset = 0;
    byte org_pc = reg.pc;

    if (reg.sr[FLAG_N] == true)
    {
        cycle_offset += 1;
        if (operand > 128)
        {
            reg.pc -= (0xff - operand + 1);
        }
        else
        {
            reg.pc += operand;
        }
    }

    if ((org_pc & 0xff00) != (reg.pc & 0xff00))
        cycle_offset += 1;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + cycle_offset;

    return;
}

void Processor::Operation31(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics AND (Address mode: indy)
    byte opcode = 0x31;
    alu.ar = reg.ac;
    alu.br = GetOperandIdY(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_AND);

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation35(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics AND (Address mode: zpgx)
    byte opcode = 0x35;
    alu.ar = reg.ac;
    alu.br = GetOperandZPX(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_AND);

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation36(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROL (Address mode: zpgx)
    byte opcode = 0x36;

    alu.ar = GetOperandAbs(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ROL));

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation38(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SEC (Address mode: impl)
    byte opcode = 0x38;

    reg.sr[FLAG_C] = true;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation39(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics AND (Address mode: absy)
    byte opcode = 0x39;
    alu.ar = reg.ac;
    alu.br = GetOperandAbY(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_AND);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation3D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics AND (Address mode: absx)
    byte opcode = 0x3D;
    alu.ar = reg.ac;
    alu.br = GetOperandAbX(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_AND);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation3E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROL (Address mode: absx)
    byte opcode = 0x3E;
    alu.ar = GetOperandAbX(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ROL));

    reg.pc += 3;
    reg.cycles_remaining = 7 - 1;

    return;
}

void Processor::Operation40(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics RTI (Address mode: impl)
    byte opcode = 0x40;

    byte sr =
        (PullByte(mem, reg) & 0b11001111) | (reg.sr.to_ulong() & 0b00110000);
    reg.sr = sr;
    byte pc = PullWord(mem, reg);
    reg.pc = pc;

    reg.pc += 1;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation41(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics EOR (Address mode: indx)
    byte opcode = 0x41;
    alu.ar = reg.ac;
    alu.br = GetOperandIdX(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_EOR);

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation45(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics EOR (Address mode: zpg)
    byte opcode = 0x45;
    alu.ar = reg.ac;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_EOR);

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation46(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LSR (Address mode: zpg)
    byte opcode = 0x46;
    alu.ar = GetOperandZP(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_LSR));

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1;

    return;
}

void Processor::Operation48(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics PHA (Address mode: impl)
    byte opcode = 0x48;
    PushByte(mem, reg, reg.ac);

    reg.pc += 1;
    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::Operation49(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics EOR (Address mode: #)
    byte opcode = 0x49;
    alu.ar = reg.ac;
    alu.br = mem.PeekByte(reg.pc, 1);

    reg.ac = alu.DoLogicalOperation(OP_EOR);

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation4A(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LSR (Address mode: A)
    byte opcode = 0x4A;
    alu.ar = reg.ac;

    reg.ac = alu.DoShiftOrRotatioin(OP_LSR);

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation4C(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics JMP (Address mode: abs)
    byte opcode = 0x4C;

    reg.pc = mem.PeekWord(reg.pc, 1);

    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::Operation4D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics EOR (Address mode: abs)
    byte opcode = 0x4D;
    alu.ar = reg.ac;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_EOR);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation4E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LSR (Address mode: abs)
    byte opcode = 0x4E;
    alu.ar = GetOperandAbs(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_LSR));

    reg.pc += 3;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation50(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BVC (Address mode: rel)
    byte opcode = 0x50;
    byte operand = mem.PeekByte(reg.pc, 1);
    byte cycle_offset = 0;
    byte org_pc = reg.pc;

    if (reg.sr[FLAG_V] == false)
    {
        cycle_offset += 1;
        if (operand > 128)
        {
            reg.pc -= (0xff - operand + 1);
        }
        else
        {
            reg.pc += operand;
        }
    }

    if ((org_pc & 0xff00) != (reg.pc & 0xff00))
        cycle_offset += 1;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + cycle_offset;

    return;
}

void Processor::Operation51(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics EOR (Address mode: indy)
    byte opcode = 0x51;
    alu.ar = reg.ac;
    alu.br = GetOperandIdY(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_EOR);

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation55(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics EOR (Address mode: zpgx)
    byte opcode = 0x55;
    alu.ar = reg.ac;
    alu.br = GetOperandZPX(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_EOR);

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation56(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LSR (Address mode: zpgx)
    byte opcode = 0x56;
    alu.ar = GetOperandZPX(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_LSR));

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation58(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CLI (Address mode: impl)
    byte opcode = 0x58;
    reg.sr[FLAG_B] = false;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation59(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics EOR (Address mode: absy)
    byte opcode = 0x59;
    alu.ar = reg.ac;
    alu.br = GetOperandAbY(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_EOR);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation5D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics EOR (Address mode: absx)
    byte opcode = 0x5D;
    alu.ar = reg.ac;
    alu.br = GetOperandAbX(mem, reg, reg.pc);

    reg.ac = alu.DoLogicalOperation(OP_EOR);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation5E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LSR (Address mode: absx)
    byte opcode = 0x5E;
    alu.ar = GetOperandAbX(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_LSR));

    reg.pc += 3;
    reg.cycles_remaining = 7 - 1;

    return;
}

void Processor::Operation60(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics RTS (Address mode: impl)
    byte opcode = 0x60;
    reg.pc = PullWord(mem, reg);

    reg.pc += 1; /// Since [PC+2] is pulled, so this is the only sensible way.
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation61(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ADC (Address mode: indx)
    byte opcode = 0x61;
    alu.ar = reg.ac;
    alu.br = GetOperandIdX(mem, reg, reg.pc);

    if (!reg.sr[FLAG_D])
        reg.ac = alu.DoAddition();
    else
        reg.ac = alu.DoBCDAddition();

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation65(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ADC (Address mode: zpg)
    byte opcode = 0x65;
    alu.ar = reg.ac;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    if (!reg.sr[FLAG_D])
        reg.ac = alu.DoAddition();
    else
        reg.ac = alu.DoBCDAddition();

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation66(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROR (Address mode: zpg)
    byte opcode = 0x66;
    alu.ar = GetOperandZP(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ROR));

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1;

    return;
}

void Processor::Operation68(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics PLA (Address mode: impl)
    byte opcode = 0x68;
    reg.ac = PullByte(mem, reg);

    reg.pc += 1;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation69(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ADC (Address mode: #)
    byte opcode = 0x69;
    alu.ar = reg.ac;
    alu.br = mem.PeekByte(reg.pc, 1);

    if (!reg.sr[FLAG_D])
        reg.ac = alu.DoAddition();
    else
        reg.ac = alu.DoBCDAddition();

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation6A(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROR (Address mode: A)
    byte opcode = 0x6A;
    alu.ar = reg.ac;

    reg.ac = alu.DoShiftOrRotatioin(OP_ROR);

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation6C(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics JMP (Address mode: ind)
    byte opcode = 0x6C;
    word addr = mem.PeekWord(mem.PeekWord(reg.pc, 1));

    reg.pc = addr;

    reg.pc += 3;
    reg.cycles_remaining = 5 - 1;

    return;
}

void Processor::Operation6D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ADC (Address mode: abs)
    byte opcode = 0x6D;
    alu.ar = reg.ac;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    if (!reg.sr[FLAG_D])
        reg.ac = alu.DoAddition();
    else
        reg.ac = alu.DoBCDAddition();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation6E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROR (Address mode: abs)
    byte opcode = 0x6E;
    alu.ar = GetOperandAbs(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ROR));

    reg.pc += 3;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation70(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BVS (Address mode: rel)
    byte opcode = 0x70;
    byte operand = mem.PeekByte(reg.pc, 1);
    byte cycle_offset = 0;
    byte org_pc = reg.pc;

    if (reg.sr[FLAG_V] == true)
    {
        cycle_offset += 1;
        if (operand > 128)
        {
            reg.pc -= (0xff - operand + 1);
        }
        else
        {
            reg.pc += operand;
        }
    }

    if ((org_pc & 0xff00) != (reg.pc & 0xff00))
        cycle_offset += 1;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + cycle_offset;
    reg.additional_cycle = false;

    return;
}

void Processor::Operation71(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ADC (Address mode: indy)
    byte opcode = 0x71;
    alu.ar = reg.ac;
    alu.br = GetOperandIdY(mem, reg, reg.pc);

    if (!reg.sr[FLAG_D])
        reg.ac = alu.DoAddition();
    else
        reg.ac = alu.DoBCDAddition();

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation75(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ADC (Address mode: zpgx)
    byte opcode = 0x75;
    alu.ar = reg.ac;
    alu.br = GetOperandZPX(mem, reg, reg.pc);

    if (!reg.sr[FLAG_D])
        reg.ac = alu.DoAddition();
    else
        reg.ac = alu.DoBCDAddition();

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation76(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROR (Address mode: zpgx)
    byte opcode = 0x76;
    alu.ar = GetOperandZPX(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ROR));

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation78(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SEI (Address mode: impl)
    byte opcode = 0x78;

    reg.sr[FLAG_B] = true;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation79(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ADC (Address mode: absy)
    byte opcode = 0x79;
    alu.ar = reg.ac;
    alu.br = GetOperandAbY(mem, reg, reg.pc);

    if (!reg.sr[FLAG_D])
        reg.ac = alu.DoAddition();
    else
        reg.ac = alu.DoBCDAddition();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation7D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ADC (Address mode: absx)
    byte opcode = 0x7D;
    alu.ar = reg.ac;
    alu.br = GetOperandAbX(mem, reg, reg.pc);

    if (!reg.sr[FLAG_D])
        reg.ac = alu.DoAddition();
    else
        reg.ac = alu.DoBCDAddition();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::Operation7E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics ROR (Address mode: absx)
    byte opcode = 0x7E;
    alu.ar = GetOperandAbX(mem, reg, reg.pc);

    mem.PutByte(reg.last_addr, alu.DoShiftOrRotatioin(OP_ROR));

    reg.pc += 3;
    reg.cycles_remaining = 7 - 1;

    return;
}

void Processor::Operation81(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STA (Address mode: indx)
    byte opcode = 0x81;
    GetOperandIdX(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.ac);

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation84(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STY (Address mode: zpg)
    byte opcode = 0x84;
    GetOperandZP(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.yr);

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::Operation85(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STA (Address mode: zpg)
    byte opcode = 0x85;
    GetOperandZP(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.ac);

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::Operation86(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STX (Address mode: zpg)
    byte opcode = 0x86;
    GetOperandZP(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.xr);

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::Operation88(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics DEY (Address mode: impl)
    byte opcode = 0x88;

    reg.yr -= 1;
    reg.sr[FLAG_N] = GetByteSignBit(reg.yr);
    reg.sr[FLAG_Z] = reg.yr == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation8A(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics TXA (Address mode: impl)
    byte opcode = 0x8A;

    reg.ac = reg.xr;
    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation8C(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STY (Address mode: abs)
    byte opcode = 0x8C;
    GetOperandAbs(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.yr);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation8D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STA (Address mode: abs)
    byte opcode = 0x8D;
    GetOperandAbs(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.ac);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation8E(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STX (Address mode: abs)
    byte opcode = 0x8E;
    GetOperandAbs(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.xr);

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation90(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BCC (Address mode: rel)
    byte opcode = 0x90;
    byte operand = mem.PeekByte(reg.pc, 1);
    byte cycle_offset = 0;
    byte org_pc = reg.pc;

    if (reg.sr[FLAG_C] == false)
    {
        cycle_offset += 1;
        if (operand > 128)
        {
            reg.pc -= (0xff - operand + 1);
        }
        else
        {
            reg.pc += operand;
        }
    }

    if ((org_pc & 0xff00) != (reg.pc & 0xff00))
        cycle_offset += 1;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + cycle_offset;
    reg.additional_cycle = false;

    return;
}

void Processor::Operation91(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STA (Address mode: indy)
    byte opcode = 0x91;
    GetOperandIdY(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.ac);

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::Operation94(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STY (Address mode: zpgx)
    byte opcode = 0x94;
    GetOperandZPX(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.yr);

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation95(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STA (Address mode: zpgx)
    byte opcode = 0x95;
    GetOperandZPX(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.ac);

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation96(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STX (Address mode: zpgy)
    byte opcode = 0x96;
    GetOperandZPY(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.xr);

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::Operation98(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics TYA (Address mode: impl)
    byte opcode = 0x98;

    reg.ac = reg.yr;
    reg.sr[FLAG_N] = GetByteSignBit(reg.yr);
    reg.sr[FLAG_Z] = reg.yr == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation99(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STA (Address mode: absy)
    byte opcode = 0x99;
    GetOperandAbY(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.ac);

    reg.pc += 3;
    reg.cycles_remaining = 5 - 1;

    return;
}

void Processor::Operation9A(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics TXS (Address mode: impl)
    byte opcode = 0x9A;

    reg.sp = reg.xr;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::Operation9D(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics STA (Address mode: absx)
    byte opcode = 0x9D;
    GetOperandAbX(mem, reg, reg.pc);
    mem.PutByte(reg.last_addr, reg.ac);

    reg.pc += 3;
    reg.cycles_remaining = 5 - 1;

    return;
}

void Processor::OperationA0(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDY (Address mode: #)
    byte opcode = 0xA0;
    reg.yr = mem.PeekByte(reg.pc, 1);

    reg.sr[FLAG_N] = GetByteSignBit(reg.yr);
    reg.sr[FLAG_Z] = reg.yr == 0;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationA1(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDA (Address mode: indx)
    byte opcode = 0xA1;
    reg.ac = GetOperandIdX(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationA2(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDX (Address mode: #)
    byte opcode = 0xA2;
    reg.xr = mem.PeekByte(reg.pc, 1);

    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationA4(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDY (Address mode: zpg)
    byte opcode = 0xA4;
    reg.yr = GetOperandZP(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.yr);
    reg.sr[FLAG_Z] = reg.yr == 0;

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationA5(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDA (Address mode: zpg)
    byte opcode = 0xA5;
    reg.ac = GetOperandZP(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationA6(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDX (Address mode: zpg)
    byte opcode = 0xA6;
    reg.xr = GetOperandZP(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationA8(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics TAY (Address mode: impl)
    byte opcode = 0xA8;

    reg.yr = reg.ac;

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationA9(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDA (Address mode: #)
    byte opcode = 0xA9;
    reg.ac = mem.PeekByte(reg.pc, 1);

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationAA(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics TAX (Address mode: impl)
    byte opcode = 0xAA;
    reg.xr = reg.ac;

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationAC(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDY (Address mode: abs)
    byte opcode = 0xAC;
    reg.yr = GetOperandAbs(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.yr);
    reg.sr[FLAG_Z] = reg.yr == 0;

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationAD(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDA (Address mode: abs)
    byte opcode = 0xAD;
    reg.ac = GetOperandAbs(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationAE(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDX (Address mode: abs)
    byte opcode = 0xAE;
    reg.xr = GetOperandAbs(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationB0(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BCS (Address mode: rel)
    byte opcode = 0xB0;
    byte operand = mem.PeekByte(reg.pc, 1);
    byte cycle_offset = 0;
    byte org_pc = reg.pc;

    if (reg.sr[FLAG_C] == true)
    {
        cycle_offset += 1;
        if (operand > 128)
        {
            reg.pc -= (0xff - operand + 1);
        }
        else
        {
            reg.pc += operand;
        }
    }

    if ((org_pc & 0xff00) != (reg.pc & 0xff00))
        cycle_offset += 1;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + cycle_offset;
    reg.additional_cycle = false;

    return;
}

void Processor::OperationB1(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDA (Address mode: indy)
    byte opcode = 0xB1;
    reg.ac = GetOperandIdY(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationB4(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDY (Address mode: zpgx)
    byte opcode = 0xB4;
    reg.yr = GetOperandZPX(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.yr);
    reg.sr[FLAG_Z] = reg.yr == 0;

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationB5(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDA (Address mode: zpgx)
    byte opcode = 0xB5;
    reg.ac = GetOperandZPX(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationB6(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDX (Address mode: zpgy)
    byte opcode = 0xB6;
    reg.xr = GetOperandZPY(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationB8(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CLV (Address mode: impl)
    byte opcode = 0xB8;
    reg.sr[FLAG_C] = false;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationB9(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDA (Address mode: absy)
    byte opcode = 0xB9;
    reg.ac = GetOperandAbY(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationBA(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics TSX (Address mode: impl)
    byte opcode = 0xBA;
    reg.xr = reg.sp;

    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationBC(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDY (Address mode: absx)
    byte opcode = 0xBC;
    reg.yr = GetOperandAbX(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.yr);
    reg.sr[FLAG_Z] = reg.yr == 0;

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationBD(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDA (Address mode: absx)
    byte opcode = 0xBD;
    reg.ac = GetOperandAbX(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.ac);
    reg.sr[FLAG_Z] = reg.ac == 0;

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationBE(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics LDX (Address mode: absy)
    byte opcode = 0xBE;
    reg.xr = GetOperandAbY(mem, reg, reg.pc);

    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationC0(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CPY (Address mode: #)
    byte opcode = 0xC0;
    alu.ar = reg.yr;
    alu.br = mem.PeekByte(reg.pc, 1);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationC1(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CMP (Address mode: indx)
    byte opcode = 0xC1;
    alu.ar = reg.ac;
    alu.br = GetOperandIdX(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationC4(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CPY (Address mode: zpg)
    byte opcode = 0xC4;
    alu.ar = reg.yr;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::OperationC5(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CMP (Address mode: zpg)
    byte opcode = 0xC5;
    alu.ar = reg.ac;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationC6(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics DEC (Address mode: zpg)
    byte opcode = 0xC6;
    alu.ar = GetOperandZP(mem, reg, reg.pc);
    alu.br = 0x1;
    byte result = alu.ar + alu.br;

    mem.PutByte(reg.last_addr, result);

    reg.sr[FLAG_N] = GetByteSignBit(result);
    reg.sr[FLAG_Z] = result == 0;

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1;

    return;
}

void Processor::OperationC8(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics INY (Address mode: impl)
    byte opcode = 0xC8;
    alu.ar = reg.yr;
    alu.br = 0x1;
    reg.yr += 1;

    reg.sr[FLAG_N] = GetByteSignBit(reg.yr);
    reg.sr[FLAG_Z] = reg.yr == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationC9(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CMP (Address mode: #)
    byte opcode = 0xC9;
    alu.ar = reg.ac;
    alu.br = mem.PeekByte(reg.pc, 1);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationCA(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics DEX (Address mode: impl)
    byte opcode = 0xCA;
    alu.ar = reg.xr;
    alu.br = 0x1;
    reg.yr -= 1;

    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationCC(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CPY (Address mode: abs)
    byte opcode = 0xCC;
    alu.ar = reg.yr;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::OperationCD(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CMP (Address mode: abs)
    byte opcode = 0xCD;
    alu.ar = reg.ac;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationCE(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics DEC (Address mode: abs)
    byte opcode = 0xCE;
    alu.ar = GetOperandAbs(mem, reg, reg.pc);
    alu.br = 0x1;
    byte result = alu.ar + alu.br;

    mem.PutByte(reg.last_addr, result);

    reg.sr[FLAG_N] = GetByteSignBit(result);
    reg.sr[FLAG_Z] = result == 0;

    reg.pc += 3;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::OperationD0(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BNE (Address mode: rel)
    byte opcode = 0xD0;
    byte operand = mem.PeekByte(reg.pc, 1);
    byte cycle_offset = 0;
    byte org_pc = reg.pc;

    if (reg.sr[FLAG_Z] == false)
    {
        cycle_offset += 1;
        if (operand > 128)
        {
            reg.pc -= (0xff - operand + 1);
        }
        else
        {
            reg.pc += operand;
        }
    }

    if ((org_pc & 0xff00) != (reg.pc & 0xff00))
        cycle_offset += 1;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + cycle_offset;
    reg.additional_cycle = false;

    return;
}

void Processor::OperationD1(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CMP (Address mode: indy)
    byte opcode = 0xD1;
    alu.ar = reg.ac;
    alu.br = GetOperandIdY(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationD5(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CMP (Address mode: zpgx)
    byte opcode = 0xD5;
    alu.ar = reg.ac;
    alu.br = GetOperandZPX(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationD6(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics DEC (Address mode: zpgx)
    byte opcode = 0xD6;
    alu.ar = GetOperandZPX(mem, reg, reg.pc);
    alu.br = 0x1;
    byte result = alu.ar + alu.br;

    mem.PutByte(reg.last_addr, result);

    reg.sr[FLAG_N] = GetByteSignBit(result);
    reg.sr[FLAG_Z] = result == 0;

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::OperationD8(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CLD (Address mode: impl)
    byte opcode = 0xD8;
    reg.sr[FLAG_D] = false;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationD9(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CMP (Address mode: absy)
    byte opcode = 0xD9;
    alu.ar = reg.ac;
    alu.br = GetOperandAbY(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationDD(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CMP (Address mode: absx)
    byte opcode = 0xDD;
    alu.ar = reg.ac;
    alu.br = GetOperandAbX(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationDE(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics DEC (Address mode: absx)
    byte opcode = 0xDE;
    alu.ar = GetOperandAbX(mem, reg, reg.pc);
    alu.br = 0x1;
    byte result = alu.ar + alu.br;

    mem.PutByte(reg.last_addr, result);

    reg.sr[FLAG_N] = GetByteSignBit(result);
    reg.sr[FLAG_Z] = result == 0;

    reg.pc += 3;
    reg.cycles_remaining = 7 - 1;

    return;
}

void Processor::OperationE0(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CPX (Address mode: #)
    byte opcode = 0xE0;
    alu.ar = reg.xr;
    alu.br = mem.PeekByte(reg.pc, 1);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationE1(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SBC (Address mode: indx)
    byte opcode = 0xE1;
    alu.ar = reg.ac;
    alu.br = GetOperandIdX(mem, reg, reg.pc);

    if (reg.sr[FLAG_D])
        reg.ac = alu.DoSubtraction();
    else
        reg.ac = alu.DoBCDSubtraction();

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationE4(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CPX (Address mode: zpg)
    byte opcode = 0xE4;
    alu.ar = reg.xr;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1;

    return;
}

void Processor::OperationE5(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SBC (Address mode: zpg)
    byte opcode = 0xE5;
    alu.ar = reg.ac;
    alu.br = GetOperandZP(mem, reg, reg.pc);

    if (reg.sr[FLAG_D])
        reg.ac = alu.DoSubtraction();
    else
        reg.ac = alu.DoBCDSubtraction();

    reg.pc += 2;
    reg.cycles_remaining = 3 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationE6(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics INC (Address mode: zpg)
    byte opcode = 0xE6;
    alu.ar = GetOperandZP(mem, reg, reg.pc);
    byte result = alu.ar + 1;

    mem.PutByte(reg.last_addr, result);

    reg.sr[FLAG_N] = GetByteSignBit(result);
    reg.sr[FLAG_Z] = result == 0;

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1;

    return;
}

void Processor::OperationE8(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics INX (Address mode: impl)
    byte opcode = 0xE8;
    reg.xr += 1;

    reg.sr[FLAG_N] = GetByteSignBit(reg.xr);
    reg.sr[FLAG_Z] = reg.xr == 0;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationE9(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SBC (Address mode: #)
    byte opcode = 0xE9;
    alu.ar = reg.ac;
    alu.br = mem.PeekByte(reg.pc, 1);

    if (reg.sr[FLAG_D])
        reg.ac = alu.DoSubtraction();
    else
        reg.ac = alu.DoBCDSubtraction();

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationEA(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics NOP (Address mode: impl)
    byte opcode = 0xEA;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationEC(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics CPX (Address mode: abs)
    byte opcode = 0xEC;
    alu.ar = reg.xr;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    alu.DoComparison();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1;

    return;
}

void Processor::OperationED(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SBC (Address mode: abs)
    byte opcode = 0xED;
    alu.ar = reg.ac;
    alu.br = GetOperandAbs(mem, reg, reg.pc);

    if (reg.sr[FLAG_D])
        reg.ac = alu.DoSubtraction();
    else
        reg.ac = alu.DoBCDSubtraction();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationEE(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics INC (Address mode: abs)
    byte opcode = 0xEE;
    alu.ar = GetOperandAbs(mem, reg, reg.pc);
    byte result = alu.ar + 1;

    mem.PutByte(reg.last_addr, result);

    reg.sr[FLAG_N] = GetByteSignBit(result);
    reg.sr[FLAG_Z] = result == 0;

    reg.pc += 3;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::OperationF0(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics BEQ (Address mode: rel)
    byte opcode = 0xF0;
    byte operand = mem.PeekByte(reg.pc, 1);
    byte cycle_offset = 0;
    byte org_pc = reg.pc;

    if (reg.sr[FLAG_Z] == true)
    {
        cycle_offset += 1;
        if (operand > 128)
        {
            reg.pc -= (0xff - operand + 1);
        }
        else
        {
            reg.pc += operand;
        }
    }

    if ((org_pc & 0xff00) != (reg.pc & 0xff00))
        cycle_offset += 1;

    reg.pc += 2;
    reg.cycles_remaining = 2 - 1 + cycle_offset;
    reg.additional_cycle = false;

    return;
}

void Processor::OperationF1(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SBC (Address mode: indy)
    byte opcode = 0xF1;
    alu.ar = reg.ac;
    alu.br = GetOperandIdY(mem, reg, reg.pc);

    if (reg.sr[FLAG_D])
        reg.ac = alu.DoSubtraction();
    else
        reg.ac = alu.DoBCDSubtraction();

    reg.pc += 2;
    reg.cycles_remaining = 5 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationF5(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SBC (Address mode: zpgx)
    byte opcode = 0xF5;
    alu.ar = reg.ac;
    alu.br = GetOperandZPX(mem, reg, reg.pc);

    if (reg.sr[FLAG_D])
        reg.ac = alu.DoSubtraction();
    else
        reg.ac = alu.DoBCDSubtraction();

    reg.pc += 2;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationF6(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics INC (Address mode: zpgx)
    byte opcode = 0xF6;
    alu.ar = GetOperandZPX(mem, reg, reg.pc);
    byte result = alu.ar + 1;

    mem.PutByte(reg.last_addr, result);

    reg.sr[FLAG_N] = GetByteSignBit(result);
    reg.sr[FLAG_Z] = result == 0;

    reg.pc += 2;
    reg.cycles_remaining = 6 - 1;

    return;
}

void Processor::OperationF8(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SED (Address mode: impl)
    byte opcode = 0xF8;

    reg.sr[FLAG_D] = true;

    reg.pc += 1;
    reg.cycles_remaining = 2 - 1;

    return;
}

void Processor::OperationF9(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SBC (Address mode: absy)
    byte opcode = 0xF9;
    alu.ar = reg.ac;
    alu.br = GetOperandAbY(mem, reg, reg.pc);

    if (reg.sr[FLAG_D])
        reg.ac = alu.DoSubtraction();
    else
        reg.ac = alu.DoBCDSubtraction();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationFD(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics SBC (Address mode: absx)
    byte opcode = 0xFD;
    alu.ar = reg.ac;
    alu.br = GetOperandAbX(mem, reg, reg.pc);

    if (reg.sr[FLAG_D])
        reg.ac = alu.DoSubtraction();
    else
        reg.ac = alu.DoBCDSubtraction();

    reg.pc += 3;
    reg.cycles_remaining = 4 - 1 + reg.additional_cycle;

    return;
}

void Processor::OperationFE(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics INC (Address mode: absx)
    byte opcode = 0xFE;
    alu.ar = GetOperandAbX(mem, reg, reg.pc);
    byte result = alu.ar + 1;

    mem.PutByte(reg.last_addr, result);

    reg.sr[FLAG_N] = GetByteSignBit(result);
    reg.sr[FLAG_Z] = result == 0;

    reg.pc += 3;
    reg.cycles_remaining = 7 - 1;

    return;
}
