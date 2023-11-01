#include <iostream>
#include <thread>

#include "Headers/Transmitter/TransmitterSource.h"
#include "Headers/Transmitter/TransmitterDestination.h"
#include "Headers/Message/AcksumByte.h"
#include "Headers/Message/HammingByte.h"

template <bool UseHamming>
struct UseHammingByte
{
    using ByteType = std::conditional_t<UseHamming, HammingByte, AcksumByte>;
};

int main()
{
    auto destination   = make_shared<TransmitterDestination>();

    // Last sesh: transmission counts feel way to low, which makes hamming code seem pointless
    auto ackSource = make_shared<TransmitterSource<UseHammingByte<true>::ByteType>>(destination);
    std::this_thread::sleep_for(std::chrono::seconds(1000));

    return 0;
}