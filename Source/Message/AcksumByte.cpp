#include "../../Headers/Message/AcksumByte.h"
#include "../../Headers/TransmissionLog.h"
#include <iostream>

int AcksumByte::GetAck()      const { return bits[ACK_INDEX]; }       // Return the ack
int AcksumByte::GetCheckSum() const { return bits[CHECKSUM_INDEX]; }  // Return the checksum

void AcksumByte::Acknowledge()    // The Transmitter 
{
    FlipBit(bits[ACK_INDEX]);
    FlipBit(bits[CHECKSUM_INDEX]);
}
bool AcksumByte::IsValid() const { return GetCheckSum() == CalculateCheckSum(); } // If GetChecksum() matches the calculation, then the checksum is valid.

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
    return sum % 2;     // Mod by 2 to turn the result into 0 if sum is even and 1 if sum is odd
}

// In order for this object to be outputted to the console via cout, this method must be defined
ostream& AcksumByte::operator<<(ostream& os)
{
    stringstream result;
    
    int count = 0;
    for (int bit : bits)        // Converts all bits to a string
    {
        result << bit;
        if (++count % 4 == 0)   // Adds a space whenever count is a multiple of 4. Note that ++count is preincrement
            result << " ";
    }

    string str = result.str();              // Converts the stringstream to a string
    cout << ToInt() << " (" << str << ")";  // Outputs the string to cout
        
    return os;
}