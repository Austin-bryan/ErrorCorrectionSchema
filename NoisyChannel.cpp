#include <random>

#include "NoisyChannel.h"
#include "TransmissionLog.h"

void NoisyChannel::ApplyNoise(Byte& byte, TransmissionLog& log)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 2);

    int noiseOdds = distribution(gen);

    if (noiseOdds != 0)
        return;
    
    int bitIndex = rand() % 10;
    log.CountNoise(bitIndex);
    byte.ApplyNoise(bitIndex);
    cout << "Noise:  " << byte << endl;
}
