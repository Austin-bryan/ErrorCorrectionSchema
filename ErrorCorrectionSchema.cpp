#include <iostream>
#include <random>

#include "Byte.h"
#include "TransmitterDestination.h"
#include "TransmitterSource.h"
#include "Evaluator.h"
#include "TransmissionLog.h"

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 255);

    auto source      = make_shared<TransmitterSource>();
    auto destination = make_shared<TransmitterDestination>();

    for (int i = 0; i < 1000; i++)
    {
        int number = distribution(gen);
        Byte byte = number;

        auto log = TransmissionLog(byte);

        cout << "\nNumber: " << byte << endl;
        source->SendTo(destination, byte, &log);

        // cout << "Original Byte: " << log.GetOriginalByte() << endl;
        cout << log << endl;
        Evaluator::AddLog(log);
    }

    Evaluator::Evaluate();
}
    