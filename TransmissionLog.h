#pragma once
#include <vector>
#include "Byte.h"

enum class EVerification { Unverified, Correct, Incorrect };

class TransmissionLog
{
public:
    TransmissionLog(Byte _originalByte);
    Byte GetOriginalByte() const;

    void CountTransmission();
    bool WasRetransmitted() const;
    void CountNoise(int bitIndex);
    void Verify(const Byte& byte);
    int GetTransmissionCount() const { return transmissionCount; }
    EVerification GetVerification() const { return verification; }
    
    friend ostream& operator<<(ostream& os, const TransmissionLog& log);
private:
    EVerification verification = EVerification::Unverified;

    Byte originalByte, finalByte;
    int transmissionCount = 0;
    int noiseCount = 0;
    vector<int> flippedIndexes;
};

inline ostream& operator<<(ostream& os, const EVerification& v)
{
    os << (v == EVerification::Unverified
        ? "Unverified"
        : v == EVerification::Correct
        ? "Correct"
        : "Incorrect");
    return os;
}
