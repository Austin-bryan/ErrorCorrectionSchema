#include "TransmitterSource.h"
#include <iostream>
#include "Byte.h"
using namespace std;

void TransmitterSource::OnMessageReceive(Transmitter* sender, Byte& byte, TransmissionLog* log)
{
    Transmitter::OnMessageReceive(sender, byte, log);

    // bool isCheckSumValid = byte.ValidateCheckSum();
    // cout << "\n*** Check sum validity: " << (isCheckSumValid ? "true" : "false") << endl;
    //
    // if (!isCheckSumValid)
    // {
        cout << "Checksum invalid; resending..." << endl;
        SendTo(sender, attemptedMessage, log);
    // }
}
void TransmitterSource::SendTo(Transmitter* receiver, Byte& byte, TransmissionLog* log)
{
    if (byte.ValidateCheckSum())
        attemptedMessage = byte;
    Transmitter::SendTo(receiver, byte, log);
}
