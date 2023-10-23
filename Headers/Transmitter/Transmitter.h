#pragma once
#include <thread>

#include "string"

struct Message;
using namespace std;

class TransmissionLog;
struct Byte;

class Transmitter : public std::enable_shared_from_this<Transmitter>
{
public:
    virtual ~Transmitter();

    Transmitter();
    Transmitter(Transmitter&&)                 = default;
    Transmitter(const Transmitter&)            = default;
    Transmitter& operator=(Transmitter&&)      = default;
    Transmitter& operator=(const Transmitter&) = default;

    virtual void SendTo(Message& message);
    virtual void OnMessageReceive(Message& message) { }

    virtual std::string GetName() { return "Base Class"; }
protected:
    virtual void ThreadMain() { }
    std::thread transmitterThread;

};