#include "alu.hxx"

ALU::ALU(Registers &reg)
    : reg(reg)
{
}

ALU::~ALU()
{
}

byte ALU::DoAddition(bool with_carry)
{
    if (this->show_debug)
        printf("%x+%x (C=%d)\n", this->ar, this->br, this->reg.sr[FLAG_C]);
    byte result = this->ar + this->br + (with_carry ? this->reg.sr[FLAG_C] : 0);

    /// Taken care of C flag
    this->reg.sr[FLAG_C] =
        (this->ar + this->br + (with_carry ? this->reg.sr[FLAG_C] : 0)) > 255;

    bool sign_res = GetByteSignBit(result);

    /// Taken care of V flag
    this->reg.sr[FLAG_V] = bool(
        (this->ar ^ result) & (this->br ^ result) & 0x80);

    /// Taken care of N and Z flag
    this->reg.sr[FLAG_Z] = result == 0;
    this->reg.sr[FLAG_N] = sign_res;

    return result;
}

byte ALU::DoSubtraction(bool with_carry)
{
    if (this->show_debug)
        printf("%x-%x (C=%d)\n", this->ar, this->br, this->reg.sr[FLAG_C]);
    byte result =
        this->ar - this->br - 1 + (with_carry ? this->reg.sr[FLAG_C] : 0);

    /// Taken care of C flag
    this->reg.sr[FLAG_C] =
        (this->ar - this->br - 1 + (with_carry ? this->reg.sr[FLAG_C] : 0)) < 0;

    bool sign_res = GetByteSignBit(result);

    /// Taken care of V flag
    this->reg.sr[FLAG_V] = bool(
        (this->ar ^ this->br) & (this->ar ^ result) & 0x80);

    /// Taken care of N and Z flag
    this->reg.sr[FLAG_Z] = result == 0;
    this->reg.sr[FLAG_N] = sign_res;

    return result;
}

byte ALU::DoBCDAddition(bool with_carry)
{
    if (this->show_debug)
        printf("%x+%x (C=%d) BCD\n", this->ar, this->br, this->reg.sr[FLAG_C]);
    word result = this->ar + this->br + (with_carry ? this->reg.sr[FLAG_C] : 0);

    if ((result & 0xf) > 0x9)
    {
        result += 0x6;
    }

    if ((result & 0xf0) > 0x90)
    {
        result += 0x60;
    }

    this->reg.sr[FLAG_C] = (result & 0xff00) != 0;
    this->reg.sr[FLAG_Z] = (result & 0xff) == 0;
    this->reg.sr[FLAG_N] = GetByteSignBit(result & 128);
    
    return static_cast<byte>(result);
}

byte ALU::DoBCDSubtraction(bool with_carry)
{
    if (this->show_debug)
        printf("%x-%x (C=%d) BCD\n", this->ar, this->br, this->reg.sr[FLAG_C]);
    word result = this->ar - this->br - 1 + 
        (with_carry ? this->reg.sr[FLAG_C] : 0);

    if ((result & 0xf) > 0x9)
    {
        result -= 0x6;
    }

    if ((result & 0xf0) > 0x90)
    {
        result -= 0x60;
    }

    this->reg.sr[FLAG_C] = !((result & 0xff00) != 0);
    this->reg.sr[FLAG_Z] = (result & 0xff) == 0;
    this->reg.sr[FLAG_N] = GetByteSignBit(result & 128);
    
    return static_cast<byte>(result);
}

byte ALU::DoLogicalOperation(const ALU_NONARITH_OP &op)
{
    if (this->show_debug)
        printf("%x,%x (OP=%x) Logical\n", this->ar, this->br, op);
    byte result = 0x00;

    switch (op) {
        case OP_AND:
            result = this->ar & this->br;
        break;
        case OP_ORA:
            result = this->ar | this->br;
        break;
        case OP_EOR:
            result = this->ar ^ this->br;
        break;
        default:
            std::__throw_runtime_error("ALU invalid logical operation");
    }

    this->reg.sr[FLAG_Z] = result == 0;
    this->reg.sr[FLAG_N] = GetByteSignBit(result);

    return result;
}

void ALU::DoBITOperation()
{
    if (this->show_debug)
        printf("%x,%x BIT\n", this->ar, this->br);
    this->reg.sr[FLAG_Z] = (this->ar & this->br) == 0;
    this->reg.sr[FLAG_N] = this->br & 0x80;
    this->reg.sr[FLAG_V] = this->br & 0x40;
}

byte ALU::DoShiftOrRotation(const ALU_NONARITH_OP &op)
{
    if (this->show_debug)
        printf("%x,%x (OP=%x) S/R\n", this->ar, this->br, op);
    byte result = this->ar;
    bool tmp = false;

    switch (op) {
        case OP_ASL:
            this->reg.sr[FLAG_C] = result & 0x80;
            result <<= 1;
        break;
        case OP_LSR:
            this->reg.sr[FLAG_C] = result & 0x01;
            result >>= 1;
        break;
        case OP_ROL:
            tmp = result & 0x80;
            result <<= 1;
            result |= this->reg.sr[FLAG_C];
            this->reg.sr[FLAG_C] = tmp;
        break;
        case OP_ROR:
            tmp = result & 0x01;
            result >>= 1;
            result |= this->reg.sr[FLAG_C] * 0x80;
            this->reg.sr[FLAG_C] = tmp;
        break;
        default:
            std::__throw_runtime_error("ALU invalid shift/rotation operation");
    }

    this->reg.sr[FLAG_N] = GetByteSignBit(result);
    this->reg.sr[FLAG_Z] = result & 0x80;

    return result;
}

void ALU::DoComparison()
{
    if (this->show_debug)
        printf("%x,%x Comparison\n", this->ar, this->br);
    this->reg.sr[FLAG_C] = this->ar >= this->br;
    this->reg.sr[FLAG_Z] = this->ar == this->br;
    this->reg.sr[FLAG_N] = this->ar < this->br;

    return;
}

void ALU::ResetALU()
{
    this->show_debug = false;
}
