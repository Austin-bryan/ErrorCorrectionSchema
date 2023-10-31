#include "../../Headers/Message/AcksumByte.h"
#include "../../Headers/TransmissionLog.h"
#include <iostream>

int AcksumByte::ToInt() const
{
    int sum = 0, pow2 = 0;

    // i starts at 7, and ends at 0. Indices 7-0 are the payload indices of the byte. 
    for (int i = 7; i > -1; i--)
        // Sum is totaled by mutliplying the bit value by the power of 2.
        // pow2++ increments the pow2 for next time, we use the value before the increment for the function call
        sum += static_cast<int>(bits[i] * pow(2, pow2++));    
    return sum;
}
int AcksumByte::GetAck()      const { return bits[ACK_INDEX]; }       // Return the ack
int AcksumByte::GetCheckSum() const { return bits[CHECKSUM_INDEX]; }  // Return the checksum

void AcksumByte::Acknowledge()
{
    FlipBit(bits[ACK_INDEX]);
    FlipBit(bits[CHECKSUM_INDEX]);
}
bool AcksumByte::IsValid() { return GetCheckSum() == CalculateCheckSum(); } // If GetChecksum() matches the calculation, then the checksum is valid.

bool AcksumByte::Verify(TransmissionLog& log)
{
    bool isValid = IsValid();

    if (isValid)                           // This step boosts accuracy by 30%, increasing from an average of 60% correct to 90% correct
        log.Verify(shared_from_this());
    else Acknowledge();

    return isValid;
}
void AcksumByte::ComputeRedundancyBits()
{
    bits.push_back(0);                      // Add the ack bit, which always starts off as 0
    bits.push_back(CalculateCheckSum());    // Add the checksum bit, after first calculating it
}
int AcksumByte::CalculateCheckSum() const
{
    int sum = 0;

    for (int i = 0; i < CHECKSUM_INDEX; i++)    // Add up all bits except the checksum, including the ack
        sum += bits[i];
    return sum % 2;                             // Mod by 2 to turn the result into 0 if sum is even and 1 if sum is odd
}