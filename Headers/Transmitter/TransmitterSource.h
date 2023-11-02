#pragma once

#include "../../Headers/Message/Byte.h"
#include "Transmitter.h"
#include <random>
#include "../../Headers/Transmitter/TransmitterSource.h"
#include "../../Headers/Transmitter/Transmitter.h"
#include "../../Headers/Evaluator.h"
#include "../../Headers/Message/ChecksumByte.h"
#include "../../Headers/Message/Byte.h"
#include "../../Headers/Message/HammingByte.h"
#include "../../Headers/Message/Message.h"

struct Message;
struct HammingByte;
struct ChecksumByte;

template<typename TByte>
class TransmitterSource : public Transmitter 
{
public:
    std::string GetName() override { return "Source"; }

    TransmitterSource(const shared_ptr<Transmitter>& _destination, int iterationCount) : iterationCount{ iterationCount }
    {
        this->destination = _destination; 
    }
    void OnMessageReceive(Message& message) override
    {
        Transmitter::OnMessageReceive(message);
        shouldResend = true;
    }

    void ThreadMain() override
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(0, 255);
    
        for (int i = 0; i < iterationCount; i++)
        {
            int number = distribution(gen);

            shared_ptr<Byte> byte = make_shared<TByte>(number);
            originalByte = make_shared<TByte>(number);

            auto log  = TransmissionLog(originalByte);
        
            Message message(destination, byte, log);
            Send(message);

            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        
            while (shouldResend)
            {
                shouldResend = false;

                // cout << "\nresend: " << message.log.GetTransmissionCount() << endl; 
                Message newMessage(message.receiver, originalByte, message.log);
                Send(newMessage);
        
                std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            }
            Evaluator::AddLog(log);
        }
        Evaluator::Evaluate();
    }
private:
    shared_ptr<Byte> originalByte;
    shared_ptr<Transmitter> destination;
    bool shouldResend = false;
    const int iterationCount;
};
