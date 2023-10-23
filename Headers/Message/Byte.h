#pragma once
#include <vector>
#include <sstream>
class TransmissionLog;
using namespace std;

struct Byte : enable_shared_from_this<Byte>
{
public:
    Byte(int number);   // Custom constructor for Byte class
    ~Byte() = default;  // Use default destructor

    Byte(const Byte& other);                // Copy constructor
    Byte& operator=(const Byte& other);     // Copy assignment

    Byte(Byte&& other) noexcept;            // Move constructor
    Byte& operator=(Byte&& other) noexcept; // Move assignment

    bool operator==(const Byte& other) const
    {
        // Ignoring checksum and ackbit increasing accuracy by 0.2%
        for (int i = 0; i < 8; i++)
            if (bits[i] != other.bits[i])
                return false;
        return true;
            
    } // Equality Operator ==
    bool operator!=(const Byte& other) const { return !(*this == other); }  // Inequality Operator !=

    void AddBit(int& number, int pow2);  // Adds a bit to the bits array
    void Acknowledge();                  // Flips ack bit and checksum bit
    void ApplyNoise(int index);          // Sends byte through noise channel
    bool ValidateCheckSum() const;       // Returns true if checksum is valid, returns false if checksum is invalid
    bool Verify(TransmissionLog& log);

    int ToInt() const;
    int GetAck() const;
    int GetCheckSum() const;

    friend ostream& operator<< (ostream& os, const Byte& byte);     // Allows outputing to cout, ex: cout << byte << endl;
private:
    const int ACK_INDEX = 8;
    const int CHECKSUM_INDEX = 9;

    vector<int> bits;               // Stores all 10 bits. 8 bits are the payload, the other 2 are the ack and checksum. 
    void FlipBit(int& bit) const;   // Flips a random bit
    int CalculateCheckSum() const;  // Sums all bits then mods by 2 to get the checksum value
};

inline bool operator==(const shared_ptr<Byte>& lhs, const shared_ptr<Byte>& rhs) { return *lhs == *rhs; }
inline bool operator!=(const shared_ptr<Byte>& lhs, const shared_ptr<Byte>& rhs) { return *lhs != *rhs; }