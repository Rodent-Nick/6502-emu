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

    word pc, last_addr;
    byte ac,xr,yr,sp,cycles_remaining;
    bool additional_cycle;
    std::bitset<8> sr{0};
};