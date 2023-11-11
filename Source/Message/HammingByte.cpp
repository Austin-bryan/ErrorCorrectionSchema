#include "../../Headers/Message/HammingByte.h"
#include "../../Headers/NoisyChannel.h"
#include "../../Headers/TransmissionLog.h"
#include "../../Headers/Message/ChecksumByte.h"

void FlipArray(std::vector<int>& arr)
{
    // The specifics of this function aren't too important, it just flips an array in reverse order
    int left = 0;
    int right = arr.size() - 1;

    while (left < right)
    {
        // Swap elements at the left and right positions
        std::swap(arr[left], arr[right]);

        // Move the left index to the right and the right index to the left
        left++;
        right--;
    }
}

// Constructor
HammingByte::HammingByte(int number): Byte{ number }
{
    int pow2 = 128;
    int index = 0;

    // This will convert the number 123 to 1000111
    while (pow2 != 0)             
    {
        AddBit(number, pow2);  
        pow2 /= 2;
    }
    FlipArray(bits); // If the number was 123, it is now 1110001. This makes the Hamming code math much easier in the future

    // Insert the redunancy bits at 0, and all the powers of 2.
    bits.insert(bits.begin(), 0);
    bits.insert(bits.begin() + 1, 0);
    bits.insert(bits.begin() + 2, 0);
    bits.insert(bits.begin() + 4, 0);
    bits.insert(bits.begin() + 8, 0);

    HammingByte::ComputeRedundancyBits();
}

bool HammingByte::IsPowerOf2(int number) const { return (number > 0 && number & number - 1) == 0; }
bool HammingByte::IsValid()
{
    vector<int> receivedParityBits(4);
    CalculateParityBits(receivedParityBits, false);     // Each parity bit is calculated as the parity of every bit in the group it controls
    int errorBitPosition = 0;

    // Calculate the errorBitPosition by combining received parity bits
    // This operation identifies the position of the error in the data
    for (int i = 0; i < 4; i++)
        errorBitPosition |= receivedParityBits[i] << i;

    // If errorBitPosition == 0, then there is no error.
    if (errorBitPosition > 0 && errorBitPosition < bits.size())
    {
        FlipBit(bits[errorBitPosition]);    // Flip the error bit to correct it
        return CalculateBit0() == bits[0];     // Check the bit0. This will detect if there was more than one bit that was flipped.
                                               // If more than one was flipped, then we need a new copy from the source.
    }
    return true;    // If we reach here, then no error was detected, so return true
}
bool HammingByte::Verify(TransmissionLog& log)
{
    bool isValid = IsValid();

    if (isValid) 
        log.Verify(shared_from_this());     // Make note of this step in the log
    return isValid;
}

int HammingByte::CalculateBit0() const { return bits[0] ^ bits[3] ^ bits[5] ^ bits[6] ^ bits[7] ^ bits[9] ^ bits[10] ^ bits[11]; }  // Get the parity of all non parity bits
int HammingByte::ToInt() const
{
    int sum = 0, pow2 = 0;

    // Sum up all non parity bits
    for (int i = 1; i < bits.size(); i++)
    {
        if (IsPowerOf2(i))
            continue;
        sum += static_cast<int>(bits[i] * pow(2, pow2++));    
    }
    return sum;
}

void HammingByte::ComputeRedundancyBits()
{
    // Computes both bit0 and calculate parity bits
    bits[0] = CalculateBit0();
    CalculateParityBits(bits, true);
}
void HammingByte::CalculateParityBits(std::vector<int>& v, bool shiftIndexes) const
{
    // Parity bit 1 controls is determined by the summed parity of any number with 0001 in it (odd numbers): 0001 (1), 0011 (3), 0111 (5), 1111 (7)...
    v[shiftIndexes ? 1 : 0] = bits[1] ^ bits[3] ^ bits[5] ^ bits[7] ^ bits[9] ^ bits[11];

    // Parity bit 2 controls is determined by the summed parity of any number with 0010 in it: 0010 (2), 0011 (3), 0110 (6), 0111 (7), 1010 (10), 1011 (11)...
    v[shiftIndexes ? 2 : 1] = bits[2] ^ bits[3] ^ bits[6] ^ bits[7] ^ bits[10] ^ bits[11];

    // Parity bit 4 controls is determined by the summed parity of any number with 0100 in it: 0100 (4), 0101 (5), 0110 (6), 0111 (7)...
    v[shiftIndexes ? 4 : 2] = bits[4] ^ bits[5] ^ bits[6] ^ bits[7];

    // Parity bit 8 controls is determined by the summed parity of any number with 1000 in it: 1000 (8), 1001 (9), 1010 (10), 1011 (11)...
    v[shiftIndexes ? 8 : 3] = bits[8] ^ bits[9] ^ bits[10] ^ bits[11];
}
bool HammingByte::operator==(const Byte& other) const
{
    // Ignoring checksum and ackbit increasing accuracy by 0.2%
    for (int i = 1; i < bits.size(); i++)
        if (!IsPowerOf2(i))
            if (bits[i] != other.GetBits()[i])
                return false;
    return true;
}