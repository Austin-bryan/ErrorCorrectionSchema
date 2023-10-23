#pragma once

#include "../../Headers/Message/Byte.h"
#include "Transmitter.h"

class Message;

class TransmitterSource : public Transmitter 
{
public:
    std::string GetName() override { return "Source"; }

    TransmitterSource(const shared_ptr<Transmitter>& _destination);
    void OnMessageReceive(Message& message) override;

    void ThreadMain() override;
private:
    shared_ptr<Byte> originalByte;
    shared_ptr<Transmitter> destination;
    // unique_ptr<Message> message;
    bool shouldResend = false;
};
