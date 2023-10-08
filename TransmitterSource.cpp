#include "TransmitterSource.h"
#include "Transmitter.h"
#include <iostream>
#include <random>

#include "Evaluator.h"
#include "Byte.h"
using namespace std;

TransmitterSource::TransmitterSource(shared_ptr<Transmitter> _destination)
{
    this->destination = _destination;
}
void TransmitterSource::OnMessageReceive(shared_ptr<Transmitter> sender, Byte& byte, TransmissionLog* log)
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
void TransmitterSource::SendTo(shared_ptr<Transmitter> receiver, Byte& byte, TransmissionLog* log)
{
    if (byte.ValidateCheckSum())
        attemptedMessage = byte;
    Transmitter::SendTo(receiver, byte, log);
}
void TransmitterSource::ThreadMain()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 255);
    
    for (int i = 0; i < 1000; i++)
    {
        int number = distribution(gen);
        Byte byte = number;

        auto log = TransmissionLog(byte);

        cout << "\nNumber: " << byte << endl;
        SendTo(destination, byte, &log);

        cout << log << endl;
        Evaluator::AddLog(log);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Evaluator::Evaluate();
}
