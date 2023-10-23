#include <iostream>

#include "../../Headers/Transmitter/TransmitterDestination.h"
#include "../../Headers/Message/Byte.h"
#include "../../Headers/Message/Message.h"
#include "../../Headers/TransmissionLog.h"
#include "../../Headers/NoisyChannel.h"

void TransmitterDestination::OnMessageReceive(const shared_ptr<Transmitter>& sender, Byte& byte, TransmissionLog& log)
{
    Transmitter::OnMessageReceive(sender, byte, log);
    bool isCheckSumValid = byte.ValidateCheckSum();
    
    if (byte.ValidateCheckSum())                // This step boosts accuracy by 30%, increasing from an average of 60% correct to 90% correct
        log.Verify(byte);
    else
    {
        byte.Acknowledge();

        Message returnMessage(sender, byte, log);
        SendTo(returnMessage);
    }
}
void TransmitterDestination::OnMessageReceive(Message& message)
{
    Transmitter::OnMessageReceive(message);
    bool isCheckSumValid = message.byte.ValidateCheckSum();
    
    if (message.byte.ValidateCheckSum())        // This step boosts accuracy by 30%, increasing from an average of 60% correct to 90% correct
        message.log.Verify(message.byte);
    else
    {
        message.byte.Acknowledge();
        SendTo(message);
    }
}
void TransmitterDestination::SendTo(Message& message)
{
    NoisyChannel::ApplyNoise(message.byte, message.log);
    message.log.CountTransmission();
    message.receiver->OnMessageReceive(message);
}
