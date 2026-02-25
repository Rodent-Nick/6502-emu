#pragma once
#include <bitset>
#include "base.hxx"
#include "reg.hxx"

enum ALU_NONARITH_OP{
    OP_AND,
    OP_ORA,
    OP_EOR,
    OP_ASL,
    OP_LSR,
    OP_ROL,
    OP_ROR,
};

class ALU{

public:
    Registers &reg;
    byte ar, br;

    ALU(Registers &reg);
    ~ALU();

    byte DoAddition(bool with_carry = true);
    byte DoSubtraction(bool with_carry = true);
    byte DoBCDAddition(bool with_carry = true);
    byte DoBCDSubtraction(bool with_carry = true);
    byte DoLogicalOperation(const ALU_NONARITH_OP &op);
    void DoBITOperation();
    byte DoShiftOrRotatioin(const ALU_NONARITH_OP &op);
    void DoComparison();

};