#include "../../Headers/Message/HammingByte.h"

#include <iostream>

#include "../../Headers/Message/AcksumByte.h"

bool HammingByte::IsValid() const
{
    return false;
}
bool HammingByte::Verify(TransmissionLog& log)
{
    return false;
}

void FlipArray(std::vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;

    while (left < right) {
        // Swap elements at the left and right positions
        std::swap(arr[left], arr[right]);

        // Move the left index to the right and the right index to the left
        left++;
        right--;
    }
}

void HammingByte::ComputeRedundancyBits()
{
    const int parityBitCount = 4; // Number of parity bits

    cout << "size: " << bits.size() << endl;
    // Calculate the parity bits
    for (int i = 0; i < parityBitCount; i++)
    {
        int parityBitPosition = 1 << i; // 2 ^ i
        int parityBit = 0;

        cout << parityBitPosition << endl;
        int position = 0;
        
        for (position = parityBitPosition; position < bits.size(); position++) 
            if ((position & parityBitPosition) != 0 )
            {
                cout << " : " << position << " " << parityBit << " " << bits.size() - position << endl;
                parityBit ^= + bits[bits.size() - position];
            }

        cout << "parity bit: " << parityBit << ", position: " << position << endl;
        bits[parityBitPosition] = parityBitPosition; // Store the calculated parity bit at the corresponding position
    }

}
int HammingByte::ToInt() const
{
    int sum = 0, pow2 = 7;

    for (int i = 0; i < bits.size(); i++)
    {
        if (IsPowerOf2(i))
            continue;
        sum += static_cast<int>(bits[i] * pow(2, pow2--));    
    }
    return sum;
}

