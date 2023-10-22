#pragma once

#include "../../Headers/Byte.h"
#include "Transmitter.h"

class Message;

class TransmitterSource : public Transmitter 
{
public:
    std::string GetName() override { return "Source"; }

    TransmitterSource(const shared_ptr<Transmitter>& _destination);
    void OnMessageReceive(const shared_ptr<Transmitter>& sender, Byte& byte, TransmissionLog& log) override;
    void SendTo(const shared_ptr<Transmitter>& receiver, Byte byte, TransmissionLog& log) override;
    void ThreadMain() override;
private:
    Byte attemptedMessage = 0;
    shared_ptr<Transmitter> destination;
    unique_ptr<Message> message;
    bool shouldResend = false;
};
