#pragma once

#include <random>
#include "Transmitter.h"
#include "../../Headers/Message/Byte.h"
#include "../../Headers/Transmitter/TransmitterSource.h"
#include "../../Headers/Evaluator.h"
#include "../../Headers/Message/Message.h"

struct Message;
struct HammingByte;
struct ChecksumByte;

// this template allows transmitter to work with either ChecksumByte or HammingByte
template<typename TByte>
class TransmitterSource : public Transmitter 
{
public:
    std::string GetName() override { return "Source"; }

    // Sets the destination to send to upon creation
    TransmitterSource(const shared_ptr<Transmitter>& _destination, int iterationCount) : iterationCount{ iterationCount } { this->destination = _destination;  }

    // Once a message is recieved, it marks a note to resend the message back to transmitter
    void OnMessageReceive(Message& message) override
    {
        Transmitter::OnMessageReceive(message);
        shouldResend = true;
    }

    // This thread executes independently of main, allowing it to wait for the reciever to send it back
    void ThreadMain() override
    {
        // The randomizer to pick a random byte value
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(0, 255);

        // Loop for the amount of times specified by the user
        for (int i = 0; i < iterationCount; i++)
        {
            int number = distribution(gen);                             // Get a random number
                                                                        
            shared_ptr<Byte> byte = make_shared<TByte>(number);            // Convert the number to a byte of a type specified by TByte
            originalByte = make_shared<TByte>(number);                     // Create a copy used for backup
                                                                        
            auto log  = TransmissionLog(originalByte);                     // Create a log to be tied with the byte
        
            Message message(destination, byte, log);                    // This message will be used to send
            Send(message);

            std::this_thread::sleep_for(std::chrono::nanoseconds(1));       // Sleep this thread for a nanosecond

            // Keep resending while we are recieving messages
            while (shouldResend)
            {
                shouldResend = false;

                Message newMessage(message.receiver, originalByte, message.log);    // Create a new message with the original byte, but reuse the log so that everything follows
                Send(newMessage);
        
                std::this_thread::sleep_for(std::chrono::nanoseconds(1));   // Send a message
            }
            Evaluator::AddLog(log);     // This message is successfully sent so add log to Evaluator
        }
        Evaluator::Evaluate();          // All iterations of been completed, so evalulate statistics
    }
private:
    shared_ptr<Byte> originalByte;          // An original copy of the byte
    shared_ptr<Transmitter> destination;    // The destination to send to
    bool shouldResend = false;
    const int iterationCount;
};
