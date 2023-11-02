#include <random>

#include "../Headers/NoisyChannel.h"
#include "../Headers/TransmissionLog.h"

void NoisyChannel::ApplyNoise(const shared_ptr<Byte>& byte, TransmissionLog& log)
{
    // Set up the random device, generator, and distribution of a range 0-3
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 3);

    int noiseOdds = distribution(gen);  // Generate random number 

    // There is a 1/4 chance noise odds = 0. This will continue to fire each time it equals zero
    while (noiseOdds == 0)
    {
        int bitIndex = rand() % 10;           // Pick a random number 0-9

        byte->ApplyNoise(bitIndex);          // Apply noise to the byte
        log.CountNoise(bitIndex);            // Tells the log file that Noise was applied
        // cout << "Noise:  " << byte << endl;

        // noiseOdds = 1;
        noiseOdds = distribution(gen);   // Generate another random number again.

        // There is a 1/16 chance this will equal 0 twice in a row (two bits flipped) and a 1/64 chance it flips 3 bits, etc.
    }

    // cout << endl;
}
