#pragma once
#include <vector>
#include <sstream>

#include "Byte.h"
class TransmissionLog;
using namespace std;

struct AcksumByte : Byte
{
public:
    AcksumByte(int number) : Byte{ number }
    {
        AcksumByte::ComputeRedundancyBits();    
    }
    AcksumByte(const Byte& other) : Byte{ other } { }
    AcksumByte(Byte&& other) : Byte{ other } { }

    void Acknowledge();                  // Flips ack bit and checksum bit
    bool IsValid() const override;
    bool Verify(TransmissionLog& log) override;
    void ComputeRedundancyBits() override;

    int GetAck() const;
    int GetCheckSum() const;

    ostream& operator<< (ostream& os) override;
    

    // friend ostream& operator<< (ostream& os, const Byte& byte);     // Allows outputing to cout, ex: cout << byte << endl;
private:
    const int ACK_INDEX = 8;
    const int CHECKSUM_INDEX = 9;

    int CalculateCheckSum() const;  // Sums all bits then mods by 2 to get the checksum value
};


