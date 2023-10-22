#pragma once
#include <memory>
#include "Transmitter.h"

class TransmitterDestination : public Transmitter 
{
public:
    std::string GetName() override { return "Destination"; }
    void OnMessageReceive(const shared_ptr<Transmitter>& sender, Byte& byte, TransmissionLog& log) override;
};
