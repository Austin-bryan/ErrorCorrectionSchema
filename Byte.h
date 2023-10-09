#pragma once
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Byte
{
public:
    Byte(int number);        // Custom constructor for Byte class
    ~Byte() = default;  // Use default destructor

    Byte(const Byte& other);                // Copy constructor
    Byte& operator=(const Byte& other);     // Copy assignment

    Byte(Byte&& other) noexcept;            // Move constructor
    Byte& operator=(Byte&& other) noexcept; // Move assignment

    bool operator==(const Byte& other) const { return bits == other.bits; } // Equality Operator ==
    bool operator!=(const Byte& other) const { return !(*this == other); }  // Inequality Operator !=

    void AddBit(int& number, int pow2);  // Adds a bit to the bits array
    void Acknowledge();             // Flips ack bit and checksum bit
    void ApplyNoise(int index);     // Sends byte through noise channel
    bool ValidateCheckSum() const;  // Returns true if checksum is valid, returns false if checksum is invalid
    
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