#include "TransmitterDestination.h"
#include "Byte.h"
#include "TransmissionLog.h"

void TransmitterDestination::OnMessageReceive(Transmitter* sender, Byte& byte, TransmissionLog* log)
{
    Transmitter::OnMessageReceive(sender, byte, log);

    bool isCheckSumValid = byte.ValidateCheckSum();
    cout << "\n*** Check sum validity: " << (isCheckSumValid ? "true" : "false") << endl;
    
    if (byte.ValidateCheckSum())        // This step boosts accuracy by 30%, increasing from an average of 60% correct to 90% correct
    {
        cout << "Message received successfully" << endl;
        log->Verify(byte);
        return;
    }
    
    byte.Acknowledge();
    SendTo(sender, byte, log);    
}
