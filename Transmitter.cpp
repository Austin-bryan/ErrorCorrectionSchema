#include <iostream>

#include "Byte.h"
#include "Transmitter.h"
#include "NoisyChannel.h"
#include "TransmissionLog.h"

using namespace std;

void Transmitter::SendTo(Transmitter* receiver, Byte& byte, TransmissionLog* log)
{
    NoisyChannel::ApplyNoise(byte, log);
    log->CountTransmission();
    receiver->OnMessageReceive(this, byte, log);    
}
void Transmitter::OnMessageReceive(Transmitter* sender, Byte& byte, TransmissionLog* log)
{
    // cout << GetName() << " has received from " << sender->GetName() << ": " << byte << endl;
}
