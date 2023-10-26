#include <iostream>
#include <thread>

#include "Headers/Message/AcksumByte.h"
#include "Headers/Transmitter/TransmitterDestination.h"
#include "Headers/Transmitter/TransmitterSource.h"
#include "Headers/Message/HammingByte.h"

int main()
{
    // auto destination = make_shared<TransmitterDestination>();
    // auto source      = make_shared<TransmitterSource>(destination);

    auto byte = make_unique<HammingByte>(1);
    std::cout << byte;

    std::this_thread::sleep_for(std::chrono::seconds(1000));
    return 0;
}