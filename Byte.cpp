#include "Byte.h"

void Byte::AddBit(int& i, int size)
{
    bits.push_back(i / size);
    i %= size;
}
Byte::Byte(int i)
{
    if (i > 255)
        throw invalid_argument("Number must be less than or equal to 255");

    int pow2 = 128;
    while (pow2 != 0)
    {
        AddBit(i, pow2);
        pow2 /= 2;
    }

    bits.push_back(0);
    bits.push_back(CalculateCheckSum());
}

int Byte::GetAck()      const { return bits[ACK_INDEX]; }
int Byte::GetCheckSum() const { return bits[CHECKSUM_INDEX]; }

int Byte::ToInt() const
{
    int sum = 0, pow2 = 0;

    for (int i = 7; i > -1; i--)
        sum += static_cast<int>(bits[i] * pow(2, pow2++));    
    return sum;
}
void Byte::Acknowledge()
{
    FlipBit(bits[ACK_INDEX]);
    FlipBit(bits[CHECKSUM_INDEX]);
}

void Byte::ApplyNoise(int index) { FlipBit(bits[index]); }
bool Byte::ValidateCheckSum() const { return GetCheckSum() == CalculateCheckSum(); }
void Byte::FlipBit(int& bit)  const { bit++; bit %= 2; }
int Byte::CalculateCheckSum() const
{
    int sum = 0;

    for (int i = 0; i < CHECKSUM_INDEX; i++)
        sum += bits[i];

    return sum % 2;
}

ostream& operator<<(ostream& os, const Byte& byte)
{
    stringstream result;
    
    int count = 0;
    for (int bit : byte.bits)
    {
        result << bit;
        if (++count % 4 == 0)
            result << " ";
    }

    string str = result.str();
    cout << byte.ToInt() << " (" << str << ")";
        
    return os;
}