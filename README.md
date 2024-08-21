# Error Detection and Correction Simulator

## Overview
This project is a C++ simulator designed to test and evaluate the effectiveness of different error detection and correction algorithms, specifically Checksum and Hamming codes.
These algorithms are critical in ensuring data integrity during transmission over potentially noisy channels. 
The project provides a framework for simulating the transmission of data, applying noise, and using these algorithms to detect and correct errors.
Multiple algorithms are used to compare and contrast different accuracy rates.

## Purpose
The primary goals of this project are to:

- **Evaluate Error Correction Methods**: Implement and test the accuracy and reliability of Checksum and Hamming code algorithms in correcting errors in data transmission.
- **Simulate Noisy Channels**: Introduce simulated noise during data transmission to replicate real-world communication challenges.
- **Log and Analyze Results**: Track the performance of these algorithms by logging transmissions, retransmissions, and error corrections, and then analyzing the results.

## Key Features

### Multiple Algorithms
#### Checksum Algorithm
- **ChecksumByte Class**: Implements a basic checksum algorithm where the sum of all bits in the byte is calculated and stored. This checksum is later compared with the recalculated checksum at the destination to verify data integrity.
- **Error Detection**: The checksum method can detect when the transmitted data has been altered, prompting a retransmission if the data is corrupted.

#### Hamming Code Algorithm
- **HammingByte Class**: Implements Hamming code, an advanced error-correcting code that not only detects but also corrects single-bit errors in the transmitted data.
- **Error Correction**: By using parity bits strategically placed within the data, the Hamming code can identify and correct errors on the fly, reducing the need for retransmission.

#### Tripled Byte Algorithm
- **TripledByte Class**: Implements a redundancy-based error correction method where each bit in the original byte is tripled, allowing the system to correct errors through majority voting.
- **Error Correction**: The algorithm consolidates every three bits into one by majority rule, correcting any single-bit errors within each triplet. This increases the resilience of data transmission against noise, as the majority of correct bits can outvote a single flipped bit.

### Transmission Simulation
- **NoisyChannel**: Simulates the effects of noise on the transmitted data, introducing errors at random to test the robustness of the error correction algorithms.
Transmitter and Receiver: Handles the sending and receiving of messages, applying noise, and checking the validity of the received data. If an error is detected that cannot be corrected, the data is retransmitted.
Logging and Evaluation
- **TransmissionLog**: Records each transmission, including the amount of noise introduced, the number of retransmissions, and whether the transmission was ultimately successful.
- **Evaluator**: Analyzes the transmission logs to evaluate the performance of the error detection and correction methods. Provides statistics such as the percentage of correct transmissions, retransmission rates, and noise occurrence.

## Installation
To compile and run the project, ensure you have a C++ compiler installed. Clone the repository and use the following commands to build and execute the program:

```
git clone https://github.com/Austin-bryan/ErrorCorrectionSchema
cd [repository-directory]
g++ -o ErrorSimulator *.cpp
./ErrorSimulator
```

## Usage
- **Run the Simulation**: Start the program to simulate the transmission of data using the implemented error detection and correction algorithms.
- **Analyze Results**: Review the logs and evaluation output to understand how effectively the algorithms corrected errors and maintained data integrity.
- **Adjust Noise Levels**: Modify the noise percentage in the NoisyChannel to see how different levels of interference affect the performance of the algorithms.

## Future Work
This project lays the groundwork for further exploration into more complex error correction techniques and their application in real-world scenarios. Future enhancements could include:

- **Implementation of Additional Algorithms**: Explore and implement other error correction methods like Reed-Solomon codes or Low-Density Parity-Check (LDPC) codes.
- **Graphical User Interface (GUI)**: Develop a GUI to visualize the transmission process, noise application, and error correction in real-time.
- **Integration with Networking Protocols**: Extend the simulation to work within a networking context, applying these algorithms to actual data transmission over a network.

## Authors
This project was developed by Austin Bryan as part of an exploration into data communication and error correction techniques.
