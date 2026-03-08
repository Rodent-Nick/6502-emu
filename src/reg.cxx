#include "reg.hxx"

Registers::Registers()
{
    this->sp = 0xff; /// Stack top
}

Registers::~Registers()
{

}

byte Registers::GetStatusRegisterAsByte()
{
    byte result = 0;
    int count = 0;
    for (auto i: this->sr){
        result |= i << count;
    }
    return result;
}

void Registers::SetStatusRegisterByByte(const byte &value)
{
    byte mask = 0b00000001;
    for (int i = 0; i < 8; i++) {
        this->sr[i] = bool(mask & value);
        mask <<= 1;
    }
    return;
}
