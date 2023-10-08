#pragma once
#include "Byte.h"
#include "Transmitter.h"

class TransmitterSource : public Transmitter 
{
public:
    std::string GetName() override { return "Source"; }

    TransmitterSource(shared_ptr<Transmitter> _destination);
    void OnMessageReceive(shared_ptr<Transmitter> sender, Byte& byte, TransmissionLog* log) override;
    void SendTo(shared_ptr<Transmitter> receiver, Byte& byte, TransmissionLog* log) override;

    void ThreadMain() override;
private:
    Byte attemptedMessage = 0;
    shared_ptr<Transmitter> destination;
};
