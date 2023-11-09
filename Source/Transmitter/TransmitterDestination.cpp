#include "../../Headers/Transmitter/TransmitterDestination.h"
#include "../../Headers/Message/Byte.h"
#include "../../Headers/Message/Message.h"

void TransmitterDestination::OnMessageReceive(Message& message)
{
    if (!message.byte->Verify(message.log))     // If the byte was not able to be verified, then send back to source to get a fresh copy
        Send(message);
}