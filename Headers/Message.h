#pragma once
#include <memory>

#include "Byte.h"
#include "../Headers/Transmitter.h"
#include "../Headers/TransmissionLog.h"

struct Message
{
    // Constructor for Message
    Message(const std::shared_ptr<Transmitter>& _receiver, Byte byte, TransmissionLog& log)
        : receiver{ _receiver }, byte{ std::move(byte) }, log{ log } {}     // Intialize all variables in the class

    std::shared_ptr<Transmitter> receiver;  // Store a shared pointer to the reciever transmitter 
    Byte byte;                              // The byte the message is transmitting
    TransmissionLog& log;                   // Hold a reference to the tranmsission log. This will get passed around and updates will be posted onto it. 
};
