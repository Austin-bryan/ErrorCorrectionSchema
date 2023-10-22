#include "../Headers/Byte.h"
#include <iostream>

// int& means that the number is passed by reference. That means that any changes to number in this function will be propagated in the function that called it
void Byte::AddBit(int& number, int pow2)
{
    /*
     * There are 3 cases of this division.
     * 1. If number is greater than a power of 2, it will be divided by the largest power of 2 that is smaller than it. ex) 200 / 128 = 1.565
     *      Since this is integer division, the result is truncated and this returns a 1, which means that power of 2 is required for the byte.
     * 2. If the number equals a power of 2, the division will be 1 exactly, and all remaining bits will be zero.
     * 3. If the number is less than a power of 2, ie 100 & 128, the devision result will be 0.X, and the integer division truncates it to zero,
     *      which means that power of 2 is not needed to represent that number
     */
    bits.push_back(number / pow2); 
    number %= pow2;     // If number > pow2, this reduces number to be the remainder, ex: 102 / 64 (bit is 1), 102 % 64 = 38.  
}
Byte::Byte(int number)
{
    // Check that the number is a valid byte size
    if (number > 255 || number < 0)
        throw invalid_argument("Number must be less than or equal to 255");     // Crash the program if the number is invalid

    int pow2 = 128;                // 128 is used here because it is the largest power of 2 of the byte
    while (pow2 != 0)              // Each loop, pow2 is divided by 2. Eventually it equals 1, and 1 / 2 is 0, because of integer division, which will terminate the loop
    {
        AddBit(number, pow2);   // Adds the bit, then reduces number. Instead of copying, number is passed by reference, which means we allow AddBit to modify the value of our number 
        pow2 /= 2;                 // Divides the current power of 2 in half, getting the next bit value
    }

    bits.push_back(0);                      // Add the ack bit, which always starts off as 0
    bits.push_back(CalculateCheckSum());    // Add the checksum bit, after first calculating it
}

Byte::Byte(const Byte& other) { bits = other.bits; }    // Copy Constructor
Byte& Byte::operator=(const Byte& other)                // Copy Assignment
{
    if (*this != other)
        bits = other.bits;
    return *this;
}
Byte::Byte(Byte&& other) noexcept { bits = std::move(other.bits); }     // Move Constrcutor
Byte& Byte::operator=(Byte&& other) noexcept                            // Move Assignment
{
    if (*this != other)
        bits = std::move(other.bits);
    return *this;
}

int Byte::GetAck()      const { return bits[ACK_INDEX]; }       // Return the ack
int Byte::GetCheckSum() const { return bits[CHECKSUM_INDEX]; }  // REturn the checksum

int Byte::ToInt() const
{
    int sum = 0, pow2 = 0;

    // i starts at 7, and ends at 0. Indices 7-0 are the payload indices of the byte. 
    for (int i = 7; i > -1; i--)
        // Sum is totaled by mutliplying the bit value by the power of 2.
        // pow2++ increments the pow2 for next time, we use the value before the increment for the function call
        sum += static_cast<int>(bits[i] * pow(2, pow2++));    
    return sum;
}
void Byte::Acknowledge()    // The Transmitter 
{
    FlipBit(bits[ACK_INDEX]);
    FlipBit(bits[CHECKSUM_INDEX]);
}

void Byte::ApplyNoise(int index)    { FlipBit(bits[index]); }                        // Flips a bit in the byte. The bit is speciifed by the parameter index
bool Byte::ValidateCheckSum() const { return GetCheckSum() == CalculateCheckSum(); }    // If GetChecksum() matches the calculation, then the checksum is valid. This does not mean the byte hasnt been changed
void Byte::FlipBit(int& bit)  const { bit++; bit %= 2; }                                // Incrementing turns 0s into 1s and 1s into 2s. Modding by 2 turns 2s into 0s, thus flipping the bit. 
int Byte::CalculateCheckSum() const
{
    int sum = 0;

    for (int i = 0; i < CHECKSUM_INDEX; i++)    // Add up all bits except the checksum, including the ack
        sum += bits[i];
    return sum % 2;     // Mod by 2 to turn the result into 0 if sum is even and 1 if sum is odd
}

// In order for this object to be outputted to the console via cout, this method must be defined
ostream& operator<<(ostream& os, const Byte& byte)
{
    stringstream result;
    
    int count = 0;
    for (int bit : byte.bits)   // Converts all bits to a string
    {
        result << bit;
        if (++count % 4 == 0)   // Adds a space whenever count is a multiple of 4. Note that ++count is preincrement
            result << " ";
    }

    string str = result.str();                   // Converts the stringstream to a string
    cout << byte.ToInt() << " (" << str << ")";  // Outputs the string to cout
        
    return os;
}