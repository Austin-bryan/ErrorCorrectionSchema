#include <random>

#include "../../Headers/Transmitter/TransmitterSource.h"
#include "../../Headers/Transmitter/Transmitter.h"
#include "../../Headers/Evaluator.h"
#include "../../Headers/Message/Byte.h"
#include "../../Headers/Message/Message.h"
#include "../../Headers/NoisyChannel.h"
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

        Message message(destination, byte, log);
        SendTo(message);

        attemptedMessage = byte;
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));

        while (shouldResend)
        {
            shouldResend = false;

            Message resend(message.receiver, attemptedMessage, message.log);
            SendTo(resend);

            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
        Evaluator::AddLog(log);
    }
    Evaluator::Evaluate();
}
