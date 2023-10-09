#include <random>
#include <iostream>

#include "NoisyChannel.h"
#include "TransmissionLog.h"

void NoisyChannel::ApplyNoise(Byte& byte, TransmissionLog& log)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 3);

    int noiseOdds = distribution(gen);
  
    while (noiseOdds == 0)
    {
        cout << noiseOdds << " ";
        
        int bitIndex = rand() % 10;
        
        log.CountNoise(bitIndex);
        byte.ApplyNoise(bitIndex);
        cout << "Noise:  " << byte << endl;
        
        noiseOdds = distribution(gen);
    }

    cout << endl;
}
