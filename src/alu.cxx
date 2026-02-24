#include "alu.hxx"

ALU::ALU(Registers &reg)
    :reg(reg)
{

}

ALU::~ALU()
{

}

byte ALU::DoAddition(bool with_carry)
{
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
    byte result = 
        this->ar - this->br + 1 - (with_carry ? this->reg.sr[FLAG_C] : 0);

    /// Taken care of C flag
    this->reg.sr[FLAG_C] = 
        (this->ar - this->br + 1 - (with_carry ? this->reg.sr[FLAG_C] : 0)) < 0;

    bool sign_res = GetByteSignBit(result);

    /// Taken care of V flag
    this->reg.sr[FLAG_V] = bool(
        (this->ar ^ this->br) & (this->ar ^ result) & 0x80);

    /// Taken care of N and Z flag
    this->reg.sr[FLAG_Z] = result == 0;
    this->reg.sr[FLAG_N] = sign_res;

    return result;
}
