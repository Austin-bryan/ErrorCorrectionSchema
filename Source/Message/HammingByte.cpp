#include "../../Headers/Message/HammingByte.h"

#include <iostream>
#include <random>

#include "../../Headers/NoisyChannel.h"
#include "../../Headers/TransmissionLog.h"
#include "../../Headers/Message/AcksumByte.h"

bool HammingByte::IsValid() const
{
    return false;
}
bool HammingByte::Verify(TransmissionLog& log)
{
    return false;
}

void HammingByte::ComputeRedundancyBits()
{
    const int parityBitCount = 4; // Number of parity bits

    // cout << "size: " << bits.size() << endl;

    // vector<int> parityBits(4);

    cout << "Hamming: ";
    for (int i = 0; i < bits.size(); i++)
    {
        cout << bits[i];
        cout << (i != 0 && (i - 3) % 4 == 0 ? " " : ""); 
    }
    cout << ", Size: " << bits.size() << endl;


    bits[0] = bits[0] ^ bits[3] ^ bits[5] ^ bits[6] ^ bits[7] ^ bits[9] ^ bits[10] ^ bits[11];
    bits[1] = bits[2] ^ bits[3] ^ bits[5] ^ bits[7] ^ bits[9] ^ bits[11];
    bits[2] = bits[4] ^ bits[3] ^ bits[6] ^ bits[7] ^ bits[10] ^ bits[11];
    bits[4] = bits[8] ^ bits[5] ^ bits[6] ^ bits[7];
    bits[8] = bits[8] ^ bits[9] ^ bits[10] ^ bits[11];

    int bitIndex = rand() % 10;         // Pick a random number 0-9
    ApplyNoise(bitIndex);               // Apply noise to the byte
    
    
    int sum = 0;
    vector<int> parityBits;
    for (int i = 0; i < bits.size(); i++)
        if (IsPowerOf2(i))
            parityBits.push_back(bits[i]);
    
    // Calculate parity bits based on the received data bits
    vector<int> receivedParityBits(4);
    receivedParityBits[0] = bits[1] ^ bits[3] ^ bits[5] ^ bits[7] ^ bits[9] ^ bits[11];
    receivedParityBits[1] = bits[2] ^ bits[3] ^ bits[6] ^ bits[7] ^ bits[10] ^ bits[11];
    receivedParityBits[2] = bits[4] ^ bits[5] ^ bits[6] ^ bits[7];
    receivedParityBits[3] = bits[8] ^ bits[9] ^ bits[10] ^ bits[11];

    // Calculate the error bit position
    int errorBitPosition = 0;
    for (int i = 0; i < 4; i++) {
        errorBitPosition |= receivedParityBits[i] << i;
    }

    cout << "Guess (" << errorBitPosition << ") == bit index (" << bitIndex << "):  " << (errorBitPosition == bitIndex ? "Accurate" : "Innacurate") << endl;
}
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

