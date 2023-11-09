#pragma once
#include <vector>
#include "Byte.h"

class TransmissionLog;
using namespace std;

/* Uses 5 parity bytes positioned at each power of 2 */
inline void FlipArray(std::vector<int>& arr);       // Flips the order of an array, 123 becomes 321

struct HammingByte : Byte
{
public:
    HammingByte(int number);                             // Constructor from an integer
    HammingByte(const Byte& other) : Byte{ other } { }   // Copy Constructor
    HammingByte(Byte&& other)      : Byte{ other } { }   // Move Constructor

    bool IsPowerOf2(int number) const;                   // Returns true if n is a power of 2
    bool IsValid() override;                             // Returns true if the byte's algorithm determines it to be true
    bool Verify(TransmissionLog& log) override;          // Calls IsValid and notifies the log of the status update
    int CalculateBit0() const;                           // Bit0 is similar to the checksum, as its a parity bit for all the bits
    int ToInt() const override;                          // Converts back to an int
    
    void ComputeRedundancyBits() override;               // Calculate all redundancy bits
    void CalculateParityBits(std::vector<int>& v, bool shiftIndexes) const;     // Calculate just the parity bits

    bool operator==(const Byte& other) const override;
};
