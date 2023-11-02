#include <iostream>
#include <thread>

#include "Headers/Transmitter/TransmitterSource.h"
#include "Headers/Transmitter/TransmitterDestination.h"
#include "Headers/Message/ChecksumByte.h"
#include "Headers/Message/HammingByte.h"

template <bool UseHamming>
struct UseHammingByte
{
    using ByteType = std::conditional_t<UseHamming, HammingByte, ChecksumByte>;
};

int main()
{
    auto destination   = make_shared<TransmitterDestination>();

    // auto source = make_shared<TransmitterSource<HammingByte>>(destination);
    auto source = make_shared<TransmitterSource<UseHammingByte<true>::ByteType>>(destination);
    std::this_thread::sleep_for(std::chrono::seconds(1000));

    return 0;
}