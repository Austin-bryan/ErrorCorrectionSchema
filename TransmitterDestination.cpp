#include "TransmitterDestination.h"
#include "Byte.h"
#include "TransmissionLog.h"

void TransmitterDestination::OnMessageReceive(const shared_ptr<Transmitter>& sender, Byte& byte, TransmissionLog& log)
{
    Transmitter::OnMessageReceive(sender, byte, log);
    std::lock_guard<std::mutex> lock(logMutex);
    bool isCheckSumValid = byte.ValidateCheckSum();
    
    cout << "**** Check sum validity: " << (isCheckSumValid ? "true" : "false") << endl;

    if (byte.ValidateCheckSum())        // This step boosts accuracy by 30%, increasing from an average of 60% correct to 90% correct
    {
        cout << "Message received successfully" << endl;
        log.Verify(byte);
        cout << log;
        return;
    }
    
    byte.Acknowledge();
    SendTo(sender, byte, log);
}
