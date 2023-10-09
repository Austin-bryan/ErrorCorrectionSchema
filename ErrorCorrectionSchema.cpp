#include <thread>

#include "TransmitterDestination.h"
#include "TransmitterSource.h"

int main()
{
    auto destination = make_shared<TransmitterDestination>();
    auto source      = make_shared<TransmitterSource>(destination);

    std::this_thread::sleep_for(std::chrono::seconds(1000));
    return 0;
}