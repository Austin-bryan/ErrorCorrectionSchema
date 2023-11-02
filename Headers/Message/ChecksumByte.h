#pragma once
#include <vector>
#include <sstream>

#include "Byte.h"
class TransmissionLog;
using namespace std;

struct ChecksumByte : Byte
{
public:
    ChecksumByte(int number) : Byte{ number }
    {
        int pow2 = 128;                // 128 is used here because it is the largest power of 2 of the byte
        while (pow2 != 0)              // Each loop, pow2 is divided by 2. Eventually it equals 1, and 1 / 2 is 0, because of integer division, which will terminate the loop
        {
            AddBit(number, pow2);   // Adds the bit, then reduces number. Instead of copying, number is passed by reference, which means we allow AddBit to modify the value of our number 
            pow2 /= 2;                 // Divides the current power of 2 in half, getting the next bit value
        }
        ChecksumByte::ComputeRedundancyBits();
    }
    ChecksumByte(const Byte& other) : Byte{ other } { }
    ChecksumByte(Byte&& other) : Byte{ other } { }

    void Acknowledge();                  // Flips ack bit and checksum bit
    bool IsValid() override;
    bool Verify(TransmissionLog& log) override;
    void ComputeRedundancyBits() override;

    bool operator==(const Byte& other) const override
    {
        // Ignoring checksum and ackbit increasing accuracy by 0.2%
        for (int i = 0; i < 8; i++)
            if (bits[i] != other.GetBits()[i])
                return false;
        return true;
    }

    int ToInt() const override;
    int GetAck() const;
    int GetCheckSum() const;
    
private:
    const int ACK_INDEX = 8;
    const int CHECKSUM_INDEX = 9;

    int CalculateCheckSum() const;  // Sums all bits then mods by 2 to get the checksum value
};


