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

    vector<int> parityBits(4);

    for (int i = 0; i < parityBits.size(); i++)
    {
        int position = 1 << i;
        int parityBit = 0;

        cout << "i: " << position << endl;
        for (int j = position - 1; j < bits.size(); j++)
        {
            if ((j & position) == position)
            {
                parityBit ^= bits[bits.size() - 1];
                cout << j << " " << bits[bits.size() - j] << ", " << parityBit << endl;
            }
        }

        cout << parityBits.size() - i - 1 << parityBit;
        parityBits[parityBits.size() - i - 1] = parityBit;
    }

    for (auto parityBit : parityBits)
        cout << "bit: " << parityBit << endl;
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

