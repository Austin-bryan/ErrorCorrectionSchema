#include <iostream>

#include "TransmitterDestination.h"
#include "Headers/Byte.h"
#include "TransmissionLog.h"

void TransmitterDestination::OnMessageReceive(const shared_ptr<Transmitter>& sender, Byte& byte, TransmissionLog& log)
{
    Transmitter::OnMessageReceive(sender, byte, log);
    bool isCheckSumValid = byte.ValidateCheckSum();
    
    // cout << "**** Check sum validity: " << (isCheckSumValid ? "true" : "false") << endl;

    if (byte.ValidateCheckSum())        // This step boosts accuracy by 30%, increasing from an average of 60% correct to 90% correct
        log.Verify(byte);
    else
    {
        byte.Acknowledge();
        SendTo(sender, byte, log);
    }
}
