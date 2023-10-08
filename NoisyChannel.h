#pragma once

#include "Byte.h"
class TransmissionLog;

class NoisyChannel 
{
public:
    static void ApplyNoise(Byte& byte, TransmissionLog& log);
};
