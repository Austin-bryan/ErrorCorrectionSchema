#include <iostream>
#include <thread>

#include "Headers/Transmitter/TransmitterSource.h"
#include "Headers/Transmitter/TransmitterDestination.h"
#include "Headers/Message/AcksumByte.h"
#include "Headers/Message/HammingByte.h"

int main()
{
    auto destination   = make_shared<TransmitterDestination>();

    bool hamming = false;

    if (!hamming)
    {
        cout << "Acksum: " << endl;
        auto ackSource = make_shared<TransmitterSource<AcksumByte>>(destination);
        std::this_thread::sleep_for(std::chrono::seconds(1000));
    }
    else
    {
        cout << "Hamming: " << endl;
        auto hammingSource = make_shared<TransmitterSource<HammingByte>>(destination);
        std::this_thread::sleep_for(std::chrono::seconds(1000));
    }

    return 0;
}