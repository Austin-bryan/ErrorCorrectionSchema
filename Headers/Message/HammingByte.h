#pragma once
#include <vector>
#include "Byte.h"

class TransmissionLog;
using namespace std;

inline void FlipArray(std::vector<int>& arr)
{
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

struct HammingByte : Byte
{
public:
    HammingByte(int number) : Byte{ number }
    {
        // cout << "HAMMING";
        int pow2 = 128;
        int index = 0;

        while (pow2 != 0)             
        {
            AddBit(number, pow2);  
            pow2 /= 2;
        }
        FlipArray(bits);

        bits.insert(bits.begin(), 0);
        bits.insert(bits.begin() + 1, 0);
        bits.insert(bits.begin() + 2, 0);
        bits.insert(bits.begin() + 4, 0);
        bits.insert(bits.begin() + 8, 0);

        // cout << this << endl;
        HammingByte::ComputeRedundancyBits();
        // cout << this << endl;

        // cout << endl;
    }
    HammingByte(const Byte& other) : Byte{ other } { }
    HammingByte(Byte&& other)      : Byte{ other } { }

    bool IsPowerOf2(int number) const { return (number > 0 && number & number - 1) == 0; }
    bool IsValid() override;
    bool Verify(TransmissionLog& log) override;
    int CalculateBit0() const;
    int ToInt() const override;
    void ComputeRedundancyBits() override;
    void CalculateParityBits(std::vector<int>& v, bool shiftIndexes) const;

    bool operator==(const Byte& other) const override
    {
        // Ignoring checksum and ackbit increasing accuracy by 0.2%
        for (int i = 1; i < bits.size(); i++)
            if (!IsPowerOf2(i))
                if (bits[i] != other.GetBits()[i])
                    return false;
        return true;
    }
};


