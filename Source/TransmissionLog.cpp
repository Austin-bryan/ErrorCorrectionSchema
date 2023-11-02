#include "../Headers/TransmissionLog.h"
#include "../Headers/Message/Byte.h"

// Constructor
TransmissionLog::TransmissionLog(shared_ptr<Byte> _originalByte)
    : originalByte{ std::move(_originalByte) }, finalByte{ nullptr } { }  // Initialize variables

shared_ptr<Byte> TransmissionLog::GetOriginalByte() const  { return originalByte; }             // Returns the original byte
void TransmissionLog::CountTransmission()
{
    transmissionCount++;
    // cout << "ID: " << ID << ", tcount: " << transmissionCount << ", " << verification << endl;
    // LogData();
} // Increments Tranmission Count
bool TransmissionLog::WasRetransmitted() const { return transmissionCount > 1; }    // Returns true if the transmission count is greater than 1
void TransmissionLog::Verify(const shared_ptr<Byte>& byte)
{
    // Verification is correct if and only if the byte matches the original, unnoise applied byte. Otherwise, its incorrect. 
    //cout << byte << ", " << originalByte << endl;
    verification = byte == originalByte ? EVerification::Correct : EVerification::Incorrect;
    finalByte = byte;
}

void TransmissionLog::CountNoise(int bitIndex)
{
    noiseCount++;                           // Count that a noise as occured
    flippedIndexes.push_back(bitIndex);     // Cache the index that was flipped. This currently is not used in the statistic display.
}
// Enables use to be printed in a 'cout <<' statement
ostream& operator<<(ostream& os, const TransmissionLog& log)
{
    os << "Original: " << log.originalByte << ", Final: " << log.finalByte << ", Transmissions: " << log.transmissionCount << ", Noises: " << log.noiseCount << ", Verification: " << log.verification << endl;
    return os;
}