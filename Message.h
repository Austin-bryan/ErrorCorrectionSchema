#pragma once
#include <memory>

#include "Transmitter.h"
#include "Byte.h"
#include "TransmissionLog.h"

class Transmitter;

struct Message
{
    Message(const std::shared_ptr<Transmitter>& _receiver, Byte byte, TransmissionLog& log) : receiver{ _receiver }, byte{ std::move(byte) }, log{ log } {}

    std::shared_ptr<Transmitter> receiver;
    Byte byte;
    TransmissionLog& log;
};
