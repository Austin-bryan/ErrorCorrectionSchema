﻿#include <random>

#include "../../Headers/Transmitter/TransmitterSource.h"
#include "../../Headers/Transmitter/Transmitter.h"
#include "../../Headers/Evaluator.h"
#include "../../Headers/Message/Byte.h"
#include "../../Headers/Message/Message.h"
using namespace std;

TransmitterSource::TransmitterSource(const shared_ptr<Transmitter>& _destination) { this->destination = _destination; }
void TransmitterSource::OnMessageReceive(const shared_ptr<Transmitter>& sender, Byte& byte, TransmissionLog& log)
{
    Transmitter::OnMessageReceive(sender, byte, log);
    
    shouldResend = true;
}
void TransmitterSource::ThreadMain()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 255);
    
    for (int i = 0; i < 10000; i++)
    {
        int number = distribution(gen);
        Byte byte = number;

        auto log = TransmissionLog(byte);

        // cout << "\nNumber: " << byte << endl;
        SendTo(destination, byte, log);

        attemptedMessage = byte;
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));

        Message message(destination, byte, log);

        while (shouldResend)
        {
            shouldResend = false;
            SendTo(message.receiver, message.byte, message.log);

            std::this_thread::sleep_for(std::chrono::nanoseconds(1));

            // if (message->byte.GetAck() == 0 &&!message->byte.ValidateCheckSum())
                // log.MarkAckFlipped();
        }

        // cout << log;
        Evaluator::AddLog(log);
    }

    // cout << endl;
    Evaluator::Evaluate();
}
