#pragma once
#include "Byte.h"
#include "Transmitter.h"

class TransmitterSource : public Transmitter 
{
public:
    std::string GetName() override { return "Source"; }

    void OnMessageReceive(Transmitter* sender, Byte& byte, TransmissionLog* log) override;
    void SendTo(Transmitter* receiver, Byte& byte, TransmissionLog* log) override;
private:
    Byte attemptedMessage = 0;
};
