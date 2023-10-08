#pragma once
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Byte
{
public:
    void AddBit(int& i, int size);
    Byte(int i);
    ~Byte() = default;

    Byte(const Byte& other) { bits = other.bits; }
    Byte& operator=(const Byte& other)
    {
        if (*this != other)
            bits = other.bits;
        return *this;
    }

    Byte(Byte&& other) noexcept { bits = std::move(other.bits); }
    Byte& operator=(Byte&& other) noexcept
    {
        if (*this != other)
            bits = std::move(other.bits);
        return *this;
    }

    bool operator==(const Byte& other) const { return bits == other.bits; }
    bool operator!=(const Byte& other) const { return !(*this == other); }

    int GetAck() const;
    int GetCheckSum() const;
    int ToInt() const;
    
    void Acknowledge();
    void ApplyNoise(int index);
    bool ValidateCheckSum() const;

    friend ostream& operator<< (ostream& os, const Byte& byte);
private:
    const int ACK_INDEX = 8;
    const int CHECKSUM_INDEX = 9;

    vector<int> bits;
    void FlipBit(int& bit) const;
    int CalculateCheckSum() const;
};