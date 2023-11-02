#include "../../Headers/Transmitter/TransmitterDestination.h"
#include "../../Headers/Message/Byte.h"
#include "../../Headers/Message/Message.h"

void TransmitterDestination::OnMessageReceive(Message& message)
{
    if (!message.byte->Verify(message.log))
        Send(message);
}

