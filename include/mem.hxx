#pragma once
#include <array>
#include <queue>
#include "base.hxx"

struct Update{
    word address;
    byte value_new;
    bool is_empty = false;
};

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
    /// This function will not push `Update` into queue.
    void PutByteExt(const word &address, const byte &value);
    void ListenAddress(const word &address);
    void UnListenAddress(const word &address);
    bool GetListenFlag(const word &address);

    std::queue<Update> message_queue;

private:
    std::array<byte, 65536> mem{0x00};
    std::array<bool, 65536> flag_listen{false};

    void AddUpdate(const word &address, const byte &value);
};

byte PeekHighByte(const word &value);
byte PeekLowByte(const word &value);
word CombineBytesIntoWord(const byte &byte_high, const byte &byte_low);