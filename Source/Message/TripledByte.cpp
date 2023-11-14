#include "../../Headers/Message/TripledByte.h"


TripledByte::TripledByte(int number): Byte{ number }
{
    TripledByte::ComputeRedundancyBits();
}
int TripledByte::ConsolidateBit(int a, int b, int c) const { return a + b + c >= 2 ? 1 : 0; }
vector<int> TripledByte::ConsolidateBits(const vector<int>& bitsToUse) const
{
    vector<int> consolidatedBits;
    for (int i = 0; i + 2 < bitsToUse.size(); i += 3)
        consolidatedBits.push_back(ConsolidateBit(bitsToUse[i], bitsToUse[i + 1], bitsToUse[i + 2]));
    return consolidatedBits;
}
bool TripledByte::IsByteValid()
{
    bits = ConsolidateBits(bits);
    return true;
}
void TripledByte::ComputeRedundancyBits()
{
    vector<int> newBits;
    for (auto bit : bits)
        for (int i = 0; i < 3; i++)
            newBits.push_back(bit);
    bits = newBits;
}
bool TripledByte::operator==(const Byte& other) const
{
    return (bits.size() == 24 ? ConsolidateBits(bits) : bits) == ConsolidateBits(other.GetBits());
}
