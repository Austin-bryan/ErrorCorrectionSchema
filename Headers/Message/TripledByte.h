#pragma once
#include "Byte.h"

using namespace std;

struct TripledByte : Byte
{
public:
    TripledByte(int number) : Byte{ number }
    {
        TripledByte::ComputeRedundancyBits();
    }
    TripledByte(const Byte& other) : Byte{ other } { }   // Copy Constructor
    TripledByte(Byte&& other)      : Byte{ other } { }   // Move Constructor

    int ConsolidateBit(int a, int b, int c) const { return a + b + c >= 2 ? 1 : 0; }
    vector<int> ConsolidateBits(const vector<int>& bitsToUse) const
    {
        vector<int> consolidatedBits;
        for (int i = 0; i + 2 < bitsToUse.size(); i += 3)
             consolidatedBits.push_back(ConsolidateBit(bitsToUse[i], bitsToUse[i + 1], bitsToUse[i + 2]));
        return consolidatedBits;
    }
    
    bool IsValid() override
    {
        bits = ConsolidateBits(bits);
        return true;
    }
    int ToInt() const override { return 1; }    // Ignore this
    void ComputeRedundancyBits() override 
    {
        vector<int> newBits;
        for (auto bit : bits)
            for (int i = 0; i < 3; i++)
                newBits.push_back(bit);
        bits = newBits;
    }
    bool operator==(const Byte& other) const override
    {
        return (bits.size() == 24 ? ConsolidateBits(bits) : bits) == ConsolidateBits(other.GetBits());
    }
};