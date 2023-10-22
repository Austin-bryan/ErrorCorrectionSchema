#include <thread>

#include "Headers/TransmitterDestination.h"
#include "Headers/TransmitterSource.h"

int main()
{
    auto destination = make_shared<TransmitterDestination>();
    auto source      = make_shared<TransmitterSource>(destination);

    std::this_thread::sleep_for(std::chrono::seconds(1000));
    return 0;
}