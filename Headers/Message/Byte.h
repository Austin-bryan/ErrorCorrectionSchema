#pragma once
#include <vector>
#include <sstream>
class TransmissionLog;
using namespace std;

struct Byte : enable_shared_from_this<Byte>
{
public:
    Byte(int number);                       // Custom constructor for Byte class
    virtual ~Byte() = default;              // Use default destructor

    Byte(const Byte& other);                // Copy constructor
    Byte& operator=(const Byte& other);     // Copy assignment

    Byte(Byte&& other) noexcept;            // Move constructor
    Byte& operator=(Byte&& other) noexcept; // Move assignment

    virtual bool operator==(const Byte& other) const = 0;
   
    // Equality Operator ==
    bool operator!=(const Byte& other) const { return !(*this == other); }  // Inequality Operator !=

    void AddBit(int& number, int pow2);  // Adds a bit to the bits array
    void ApplyNoise(int index);          // Sends byte through noise channel
    
    virtual bool Verify(TransmissionLog& log) = 0;
    virtual bool IsValid() const = 0;                // Returns true if checksum is valid, returns false if checksum is invalid
    virtual void ComputeRedundancyBits() = 0;
    virtual ostream& operator<< (ostream& os) = 0;   // Allows outputing to cout, ex: cout << byte << endl;

    int ToInt() const;

    const vector<int>& GetBits() const { return bits; }
protected:
    vector<int> bits;               // Stores all 10 bits. 8 bits are the payload, the other 2 are the ack and checksum. 
    void FlipBit(int& bit) const;   // Flips a random bit
};

inline bool operator==(const shared_ptr<Byte>& lhs, const shared_ptr<Byte>& rhs) { return *lhs == *rhs; }
inline bool operator!=(const shared_ptr<Byte>& lhs, const shared_ptr<Byte>& rhs) { return *lhs != *rhs; }