#include "../../Headers/Message/Message.h"
#include "../../Headers/Transmitter/Transmitter.h"
#include "../../Headers/NoisyChannel.h"
#include "../../Headers/TransmissionLog.h"

using namespace std;

Transmitter::Transmitter()
{
    transmitterThread = std::thread([this] { this->ThreadMain(); });    // Create thread
}
Transmitter::~Transmitter()
{
    if (transmitterThread.joinable())      // Delete thread when the trasmitter is destroyed
        transmitterThread.join();
}

void Transmitter::Send(Message& message)
{
    NoisyChannel::ApplyNoise(message.byte, message.log);                    // Apply noise to message
    message.log.CountTransmission();                                           // Count this send operation in the log function

    Message newMessage (shared_from_this(), message.byte, message.log);     // Create a new message to be recieved by the reciever
    message.receiver->OnMessageReceive(newMessage);                         // Notify the reciever of the recieved message
}