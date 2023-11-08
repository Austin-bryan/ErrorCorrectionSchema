#include "../../Headers/Message/HammingByte.h"
#include "../../Headers/NoisyChannel.h"
#include "../../Headers/TransmissionLog.h"
#include "../../Headers/Message/ChecksumByte.h"

bool HammingByte::IsValid()
{
    vector<int> receivedParityBits(4);
    CalculateParityBits(receivedParityBits, false);

    int errorBitPosition = 0;
    for (int i = 0; i < 4; i++)
        errorBitPosition |= receivedParityBits[i] << i;
    if (errorBitPosition > 0 && errorBitPosition < bits.size())
    {
        bits[errorBitPosition] = !bits[errorBitPosition];
        return CalculateBit0() == bits[0];
    }
    return true;
}
bool HammingByte::Verify(TransmissionLog& log)
{
    bool isValid = IsValid();

    if (isValid) 
        log.Verify(shared_from_this());
    return isValid;
}

int HammingByte::CalculateBit0() const { return bits[0] ^ bits[3] ^ bits[5] ^ bits[6] ^ bits[7] ^ bits[9] ^ bits[10] ^ bits[11]; }
int HammingByte::ToInt() const
{
    int sum = 0, pow2 = 0;

    for (int i = 1; i < bits.size(); i++)
    {
        if (IsPowerOf2(i))
            continue;
        sum += static_cast<int>(bits[i] * pow(2, pow2++));    
    }
    return sum;
}

void HammingByte::ComputeRedundancyBits()
{
    bits[0] = CalculateBit0();
    CalculateParityBits(bits, true);
}
void HammingByte::CalculateParityBits(std::vector<int>& v, bool shiftIndexes) const
{
    v[shiftIndexes ? 1 : 0] = bits[1] ^ bits[3] ^ bits[5] ^ bits[7] ^ bits[9] ^ bits[11];
    v[shiftIndexes ? 2 : 1] = bits[2] ^ bits[3] ^ bits[6] ^ bits[7] ^ bits[10] ^ bits[11];
    v[shiftIndexes ? 4 : 2] = bits[4] ^ bits[5] ^ bits[6] ^ bits[7];
    v[shiftIndexes ? 8 : 3] = bits[8] ^ bits[9] ^ bits[10] ^ bits[11];
}

