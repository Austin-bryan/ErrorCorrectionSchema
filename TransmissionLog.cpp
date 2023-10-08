#include "TransmissionLog.h"
#include "Byte.h"

TransmissionLog::TransmissionLog(Byte _originalByte) : originalByte{ std::move(_originalByte) }, finalByte{ 0 } { }

Byte TransmissionLog::GetOriginalByte() const  { return originalByte; }
void TransmissionLog::CountTransmission()      { transmissionCount++; }
bool TransmissionLog::WasRetransmitted() const { return transmissionCount > 1; }
void TransmissionLog::Verify(const Byte& byte)
{
    verification = byte == originalByte ? EVerification::Correct : EVerification::Incorrect;
    finalByte = byte;
}

void TransmissionLog::CountNoise(int bitIndex)
{
    noiseCount++;
    flippedIndexes.push_back(bitIndex);
}
ostream& operator<<(ostream& os, const TransmissionLog& log)
{
    os << "Original: " << log.originalByte << ", Final: " << log.finalByte << ", Transmissions: " << log.transmissionCount << ", Noises: " << log.noiseCount << ", Verification: " << log.verification << endl;
    return os;
}
