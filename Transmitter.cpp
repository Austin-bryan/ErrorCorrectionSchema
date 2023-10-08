#include <iostream>

#include "Byte.h"
#include "Transmitter.h"
#include "NoisyChannel.h"
#include "TransmissionLog.h"

using namespace std;

Transmitter::Transmitter()
{
    transmitterThread = std::thread([this] { this->ThreadMain(); });
}
Transmitter::~Transmitter()
{
    if (transmitterThread.joinable())
        transmitterThread.join();
}

void Transmitter::SendTo(const shared_ptr<Transmitter>& receiver, Byte& byte, TransmissionLog& log)
{
    NoisyChannel::ApplyNoise(byte, log);
    log.CountTransmission();
    receiver->OnMessageReceive(shared_from_this(), byte, log);    
}
void Transmitter::OnMessageReceive(const shared_ptr<Transmitter>& sender, Byte& byte, TransmissionLog& log)
{
    // cout << GetName() << " has received from " << sender->GetName() << ": " << byte << endl;
}
