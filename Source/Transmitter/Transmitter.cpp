#include <iostream>

#include "../../Headers/Message/Byte.h"
#include "../../Headers/Message/Message.h"
#include "../../Headers/Transmitter/Transmitter.h"
#include "../../Headers/NoisyChannel.h"
#include "../../Headers/TransmissionLog.h"

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

void Transmitter::SendTo(Message& message)
{
    NoisyChannel::ApplyNoise(message.byte, message.log);
    message.log.CountTransmission();

    Message newMessage (shared_from_this(), message.byte, message.log);
    message.receiver->OnMessageReceive(newMessage); 
}