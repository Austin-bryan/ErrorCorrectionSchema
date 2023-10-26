#pragma once
#include <vector>
#include "Byte.h"

class TransmissionLog;
using namespace std;

struct HammingByte : Byte
{
public:
    HammingByte(int number)        : Byte{ number }
    {
        int pow2 = 128;
        int index = 0;

        bits.push_back(0);
        while (pow2 != 0)             
        {
            index++;
            if (IsPowerOf2(index))
                bits.push_back(0);
            else
            {
                AddBit(number, pow2);  
                pow2 /= 2;
            }
        }
        HammingByte::ComputeRedundancyBits();
    }
    HammingByte(const Byte& other) : Byte{ other } { }
    HammingByte(Byte&& other)      : Byte{ other } { }

    bool IsPowerOf2(int number) const { return (number > 0 && number & number - 1) == 0; }
    bool IsValid() const override;
    bool Verify(TransmissionLog& log) override;
    void ComputeRedundancyBits() override;
    int ToInt() const override;

    bool operator==(const Byte& other) const override
    {
        // Ignoring checksum and ackbit increasing accuracy by 0.2%
        for (int i = 0; i < 8; i++)
            if (bits[i] != other.GetBits()[i])
                return false;
        return true;
    }
};


