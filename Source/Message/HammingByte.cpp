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

void HammingByte::ComputeRedundancyBits()
{
    const int parityBitCount = 4; // Number of parity bits

    // cout << "size: " << bits.size() << endl;

    vector<int> parityBits(4);

    cout << "Hamming: ";
    for (auto bit : bits)
        cout << bit;
    cout << ", Size: " << bits.size() << endl;
    // 0  1  2  3  4  5  6  7   8   9
    // p0 p1 p2 d1 d2 d4 d8 d16 d32 d64

    for (int i = 0; i < bits.size(); i++)
        cout << "bits["<< i <<"] = " << bits[i] << endl;
    cout << endl;

    cout << "bits[1] = " << bits[3] << "^" << bits[5] << "^" << bits[7] << " = " << (bits[3] ^ bits[5] ^ bits[7]) << endl;
    cout << "bits[2] = " << bits[3] << "^" << bits[6] << "^" << bits[7] << " = " << (bits[3] ^ bits[6] ^ bits[7]) << endl;
    cout << "bits[4] = " << bits[5] << "^" << bits[5] << "^" << bits[7] << " = " << (bits[5] ^ bits[5] ^ bits[7]) << endl;

    bits[1] = bits[3] ^ bits[5] ^ bits[7];
    bits[2] = bits[3] ^ bits[6] ^ bits[7];
    bits[4] = bits[5] ^ bits[5] ^ bits[7];

    cout << "With parity Bits: " << this;
    cout << endl;
}
int HammingByte::ToInt() const
{
    int sum = 0, pow2 = 0;

    for (int i = 1; i < bits.size(); i++)
    {
        if (IsPowerOf2(i))
            continue;
        sum += static_cast<int>(bits[i] * pow(2, pow2++));    
    }
    return sum;
}

