#pragma once
#include <bitset>
#include "base.hxx"
#include "reg.hxx"

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
    byte DoLogicalOperation();
    byte DoShiftOrRotatioin();
    void DoComparison();

};