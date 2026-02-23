#pragma once
#include "base.hxx"
#include <bitset>

enum STATUS_REGISTER_FLAG{
    FLAG_C,
    FLAG_Z,
    FLAG_I,
    FLAG_D,
    FLAG_B,
    FLAG_IGNORED,
    FLAG_V,
    FLAG_N
};

class Registers{
public:
    Registers();
    ~Registers();

    word pc;
    byte ac,xr,yr,sp;
    std::bitset<8> sr{0};
};