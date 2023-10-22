#pragma once

#include "../Headers/Message/Byte.h"
class TransmissionLog;      // Forward declare Transmission Log to avoid having to use #include

class NoisyChannel 
{
public:
    static void ApplyNoise(Byte& byte, TransmissionLog& log);   // Define function Apply noise to take a reference to a byte and reference to a log
};
