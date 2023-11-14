#pragma once
#include "Byte.h"

using namespace std;

struct TripledByte : Byte
{
public:
    TripledByte(int number);
    TripledByte(const Byte& other) : Byte{ other } { }   // Copy Constructor
    TripledByte(Byte&& other)      : Byte{ other } { }   // Move Constructor

    int ConsolidateBit(int a, int b, int c) const;
    vector<int> ConsolidateBits(const vector<int>& bitsToUse) const;

    bool IsByteValid() override;
    int ToInt() const override { return 1; }    // Ignore this
    void ComputeRedundancyBits() override;
    bool operator==(const Byte& other) const override;
};