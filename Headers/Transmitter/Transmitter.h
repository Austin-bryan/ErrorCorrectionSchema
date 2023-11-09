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

    Transmitter();                                          // Constructor
    Transmitter(Transmitter&&)                 = default;   // Move Constructor
    Transmitter(const Transmitter&)            = delete;    // Copy Constructor
    Transmitter& operator=(Transmitter&&)      = default;   // Move Assignment Operator
    Transmitter& operator=(const Transmitter&) = delete;    // Copy Assignment Operator

    virtual void Send(Message& message);                    // Send a message between transmitters
    virtual void OnMessageReceive(Message& message) { }     // Called when a message recieves a message

    virtual std::string GetName() { return "Base Class"; }  // Used for name outputting
protected:
    virtual void ThreadMain() { }   
    std::thread transmitterThread;
};