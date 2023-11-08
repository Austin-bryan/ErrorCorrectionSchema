#include <iostream>
#include <thread>

#include "Headers/NoisyChannel.h"
#include "Headers/Transmitter/TransmitterSource.h"
#include "Headers/Transmitter/TransmitterDestination.h"
#include "Headers/Message/ChecksumByte.h"
#include "Headers/Message/HammingByte.h"

template <bool UseHamming>
struct UseHammingByte
{
    using ByteType = std::conditional_t<UseHamming, HammingByte, ChecksumByte>;
};

int GetIterationCount();
double GetErrorRatio();
bool UseHamming();

int main()
{
    cout << "Welcome to the Discrete Gang's Error Correction Schema." << endl;

    NoisyChannel::NoisePercentage = GetErrorRatio();
    auto destination = make_shared<TransmitterDestination>();

    if (UseHamming())
    {
        auto source = make_shared<TransmitterSource<UseHammingByte<true>::ByteType>>(destination, GetIterationCount());
        std::this_thread::sleep_for(std::chrono::seconds(1000));
    }
    else
    {
        auto source = make_shared<TransmitterSource<UseHammingByte<false>::ByteType>>(destination, GetIterationCount());
        std::this_thread::sleep_for(std::chrono::seconds(1000));
    }


    return 0;
}

int GetIterationCount()
{
    system("cls");
    
    const int MIN_ITERATIONS = 100, MAX_ITERATIONS = 1000000;
    cout << "Enter how many iterations you want. The number must be between " << MIN_ITERATIONS << " and " << MAX_ITERATIONS << ": ";

    int iterationCount;
    cin >> iterationCount;

    while (iterationCount < MIN_ITERATIONS || iterationCount > MAX_ITERATIONS)
    {
        cout << "Invalid input. Input must be between " << MIN_ITERATIONS << " and " << MAX_ITERATIONS << ". Try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> iterationCount;
    }

    return iterationCount;
}
double GetErrorRatio()
{
    cout << endl << "Enter how often a bit should be flipped. As a percentage, " <<
                    "the value should be between 0% (no bits will be flipped) and 99% (a bit will be flipped almost every transmission): ";
    double percentage = 0;
    cin >> percentage;

    while (percentage < 0 || percentage > 99)
    {
        cout << "Invalid input. Input must be between 0 and 99. Try again: ";
        cin >> percentage;
    }

    cout << endl;
    cout << "You've chosen " << percentage << "%, which means: " << endl;
    cout << percentage << "% of transmissions will have at least one bit flip" << endl;
    cout << percentage * percentage / 100 << "% of transmissions will have at least two bit flips" << endl;
    cout << pow(percentage, 3) / 10000 << "% of transmissions will have at least three bit flips." << endl;
    cout << pow(percentage, 4) / 1000000 << "% of transmissions will have at least four bit flips, and so on." << endl << endl;

    cout << "Press any key to continue... ";

    char buffer;
    cin >> buffer;

    return percentage;
}
bool UseHamming()
{
    system("cls");

    cout << "There are two different algorithms you can use: " << endl;
    cout << "1. Ack/Checksum method: Adds 2 bits of redundancy. It is able to detect a multiple bit errors but not fix them." << endl;
    cout << "2. Hamming Code: adds 5 redundant parity bits, giving enough redundancy to fix single bit errors, and detect 2 or more bit errors." << endl;
    cout << "Take your pick: ";

    int input;
    cin >> input;

    while (input < 1 || input > 2)
    {
        cout << "Invalid input. Input must be either 1 or 2. Try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> input;
    }

    return input == 2;
}
