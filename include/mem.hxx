#pragma once
#include <array>
#include "base.hxx"

class Memory
{

public:
    Memory();
    ~Memory();
    void ResetMemory();
    byte PeekByte(const word &address, const byte &offset = 0);
    word PeekWord(const word &address, const byte &offset = 0);
    void PutByte(const word &address, const byte &value);
    void PutWord(const word &address, const word &value);

private:
    std::array<byte, 65536> mem{0x00};
};

byte PeekHighByte(const word &value);
byte PeekLowByte(const word &value);
word CombineBytesIntoWord(const byte &byte_high, const byte &byte_low);