#pragma once
#include "string"

class TransmissionLog;
struct Byte;

class Transmitter
{
public:
    virtual ~Transmitter() = default;

    Transmitter()                              = default;
    Transmitter(Transmitter&&)                 = default;
    Transmitter(const Transmitter&)            = default;
    Transmitter& operator=(Transmitter&&)      = default;
    Transmitter& operator=(const Transmitter&) = default;

    virtual void SendTo(Transmitter* receiver, Byte& byte, TransmissionLog* log);
    virtual void OnMessageReceive(Transmitter* sender, Byte& byte, TransmissionLog* log);

    virtual std::string GetName() { return "Base Class"; }
};