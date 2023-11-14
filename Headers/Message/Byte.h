#pragma once
#include <vector>
#include <sstream>
class TransmissionLog;
using namespace std;

// Checksum swag = Checksum(4);
struct Byte : enable_shared_from_this<Byte> 
{
public:
    Byte(int number);                       // Custom constructor for Byte class
    virtual ~Byte() = default;              // Use default destructor

    Byte(const Byte& other);                // Copy constructor
    Byte& operator=(const Byte& other);     // Copy assignment

    Byte(Byte&& other) noexcept;            // Move constructor
    Byte& operator=(Byte&& other) noexcept; // Move assignment

    virtual bool operator==(const Byte& other) const = 0;   // This is virtual so that ChecksumByte and Hamming Byte can define their own equality functions
   
    // Equality Operator ==
    bool operator!=(const Byte& other) const { return !(*this == other); }  // Inequality Operator !=

    void AddBit(int& number, int pow2);              // Adds a bit to the bits array
    void ApplyNoise(int index);                      // Sends byte through noise channel
    virtual bool ShouldRetransmit(TransmissionLog& log);       // Makes sure Byte is valid, and makes a note of it in the log
    virtual bool IsByteValid() = 0;                      // Returns true if checksum is valid, returns false if checksum is invalid
    virtual void ComputeRedundancyBits() = 0;        // Computes the bits that will be used for error detection
    virtual int ToInt() const = 0;                   // Conver to integer
    virtual int Size() const { return bits.size(); };
    
    friend ostream& operator<<(ostream& os, const Byte* byte);
    const vector<int>& GetBits() const { return bits; }
protected:
    vector<int> bits;               // Stores all 10 bits. 8 bits are the payload, the other 2 are the ack and checksum. 
    void FlipBit(int& bit) const;   // Flips a random bit
};

// Define equality operators that work with the shared pointers of Byte
inline bool operator==(const shared_ptr<Byte>& lhs, const shared_ptr<Byte>& rhs) { return *lhs == *rhs; }
inline bool operator!=(const shared_ptr<Byte>& lhs, const shared_ptr<Byte>& rhs) { return *lhs != *rhs; }

