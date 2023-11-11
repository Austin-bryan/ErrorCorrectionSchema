#pragma once
#include <vector>

#include "Byte.h"
class TransmissionLog;
using namespace std;

/* Uses a checksum and ack bit */
struct ChecksumByte : Byte
{
public:
    ChecksumByte(int number);
    ChecksumByte(const Byte& other) : Byte{ other } { }
    ChecksumByte(Byte&& other) : Byte{ other } { }

    void Acknowledge();                             // Flips ack bit and checksum bit
    bool IsValid() override;                        // Returns true if Byte is valid
    bool Verify(TransmissionLog& log) override;     // Makes sure Byte is valid, and makes a note of it in the log
    void ComputeRedundancyBits() override;          // Computes the bits that will be used for error detection

    bool operator==(const Byte& other) const override;

    int ToInt() const override;     // Convert byte to intgger
    int GetAck() const;             // Return ack value
    int GetCheckSum() const;        // Return checksum value
    
private:
    const int ACK_INDEX = 8;
    const int CHECKSUM_INDEX = 9;

    int CalculateCheckSum() const;  // Sums all bits then mods by 2 to get the checksum value
};


