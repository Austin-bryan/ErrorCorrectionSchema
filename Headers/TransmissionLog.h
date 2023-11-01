#pragma once
#include <vector>
#include "../Headers/Message/Byte.h"

// Three States of verification. It starts in Unverified, but should always end in Correct or Incorrect. 
enum class EVerification { Unverified, Correct, Incorrect };

/*
 * This class holds onto various factors that occur during transmission, as described by the methods and fields.
 * There is one transmission log per transmission. Each instance gets passed around by reference so chances will accumlate.
 * At the end, the evaluator will loop through all logs and sum and average data stored in this log objects. 
 */
class TransmissionLog
{
public:
    TransmissionLog(shared_ptr<Byte> _originalByte);
    shared_ptr<Byte> GetOriginalByte() const;

    void CountTransmission();
    bool WasRetransmitted() const;
    void CountNoise(int bitIndex);
    void Verify(const shared_ptr<Byte>& byte);
    void MarkAckFlipped()                 { wasAckFlipped = true; }
    int GetNoiseCount()             const { return noiseCount; }
    int GetTransmissionCount()      const { return transmissionCount; }
    bool GetWasAckFlipped()         const { return wasAckFlipped; }
    EVerification GetVerification() const { return verification; }

    void LogData() const { cout << ID << ": " << transmissionCount << ", "; }

    friend ostream& operator<<(ostream& os, const TransmissionLog& log);
private:
    // This data is hidden to prevent mutation from outside this class. 
    EVerification verification = EVerification::Unverified;

    shared_ptr<Byte> originalByte, finalByte;   
    int transmissionCount = 0;
    int noiseCount = 0;
    bool wasAckFlipped = false;
    int ID;
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
