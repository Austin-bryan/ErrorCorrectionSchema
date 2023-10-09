#include "TransmitterSource.h"
#include "Transmitter.h"
#include <iostream>
#include <random>

#include "Evaluator.h"
#include "Byte.h"
#include "Message.h"
using namespace std;

TransmitterSource::TransmitterSource(const shared_ptr<Transmitter>& _destination) { this->destination = _destination; }
void TransmitterSource::OnMessageReceive(const shared_ptr<Transmitter>& sender, Byte& byte, TransmissionLog& log)
{
    Transmitter::OnMessageReceive(sender, byte, log);
    
    // cout << "...Checksum invalid; resending..." << endl;
    // SendTo(destination, attemptedMessage, log);

    cout << "Receive Message" << endl;

    std::lock_guard<std::mutex> lock(logMutex);
    
    message = make_unique<Message>(sender, byte, log);
    t = true;
    cout << "Message is 1st null: " << t << endl;

}
void TransmitterSource::SendTo(const shared_ptr<Transmitter>& receiver, Byte& byte, TransmissionLog& log)
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
    
    for (int i = 0; i < 100; i++)
    {
        int number = distribution(gen);
        Byte byte = number;

        auto log = TransmissionLog(byte);

        cout << "\nNumber: " << byte << endl;
        SendTo(destination, byte, log);

        std::this_thread::sleep_for(std::chrono::microseconds(1));

        while (t)
        {
            cout << "...Checksum invalid; resending..." << endl;
    
            t = false;

            
            SendTo(message->receiver, attemptedMessage, message->log);
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }

        cout << log;
        Evaluator::AddLog(log);
    }

    Evaluator::Evaluate();
}
