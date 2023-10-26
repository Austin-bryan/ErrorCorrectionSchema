#include "../../Headers/Message/Byte.h"
#include "../../Headers/TransmissionLog.h"
#include <iostream>

Byte::Byte(int number)
{
    // Check that the number is a valid byte size
    if (number > 255 || number < 0)
        throw invalid_argument("Number must be less than or equal to 255");     // Crash the program if the number is invalid

    // int pow2 = 128;                // 128 is used here because it is the largest power of 2 of the byte
    // while (pow2 != 0)              // Each loop, pow2 is divided by 2. Eventually it equals 1, and 1 / 2 is 0, because of integer division, which will terminate the loop
    // {
    //     AddBit(number, pow2);   // Adds the bit, then reduces number. Instead of copying, number is passed by reference, which means we allow AddBit to modify the value of our number 
    //     pow2 /= 2;                 // Divides the current power of 2 in half, getting the next bit value
    // }
}

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

Byte::Byte(const Byte& other) : enable_shared_from_this(other) { bits = other.bits; }    // Copy Constructor
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



void Byte::ApplyNoise(int index) { FlipBit(bits[index]); }                        // Flips a bit in the byte. The bit is speciifed by the parameter index
void Byte::FlipBit(int& bit)  const { bit++; bit %= 2; } // Incrementing turns 0s into 1s and 1s into 2s. Modding by 2 turns 2s into 0s, thus flipping the bit. 