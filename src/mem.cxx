#include "mem.hxx"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void Memory::ResetMemory()
{
    for (auto i : this->mem)
    {
        i = 0x00;
    }
    return;
}

byte Memory::PeekByte(const word &address, const byte &offset)
{
    return this->mem[address + offset];
}

word Memory::PeekWord(const word &address, const byte &offset)
{
    return (static_cast<word>(this->mem[address + offset + 1]) << 8)
        | this->mem[address + offset];
}

void Memory::PutByte(const word &address, const byte &value)
{
    this->mem[address] = value;
    return;
}

void Memory::PutWord(const word &address, const word &value)
{
    this->mem[address] = PeekHighByte(value);
    this->mem[address + 1] = PeekLowByte(value);
    return;
}

byte PeekHighByte(const word &value){
    return static_cast<uint8_t>(value & 0x00ff);
}

byte PeekLowByte(const word &value){
    return static_cast<uint8_t>(value >> 8);
}

word CombineBytesIntoWord(const byte &byte_high, const byte &byte_low){
    return (static_cast<uint16_t>(byte_high) << 8) | byte_low;
}
