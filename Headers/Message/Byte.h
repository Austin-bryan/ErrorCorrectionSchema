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
    void ApplyNoise(int index);          // Sends byte through noise channel
    virtual bool Verify(TransmissionLog& log) { return false; }
    virtual bool IsValid() const { return false; }                // Returns true if checksum is valid, returns false if checksum is invalid
    virtual void ComputeRedundancyBits() { }

    int ToInt() const;

    virtual ostream& operator<< (ostream& os) { return os; }    // Allows outputing to cout, ex: cout << byte << endl;
protected:

    vector<int> bits;               // Stores all 10 bits. 8 bits are the payload, the other 2 are the ack and checksum. 
    void FlipBit(int& bit) const;   // Flips a random bit
};

inline bool operator==(const shared_ptr<Byte>& lhs, const shared_ptr<Byte>& rhs) { return *lhs == *rhs; }
inline bool operator!=(const shared_ptr<Byte>& lhs, const shared_ptr<Byte>& rhs) { return *lhs != *rhs; }