#include <gtest/gtest.h>
#include "../Headers/Message/HammingByte.h"
#include "../Headers/TransmissionLog.h"
#include "MockClasses.h"

// Test constructor initializes bits correctly
TEST(HammingByteTest, ConstructorInitializesBitsCorrectly) {
  HammingByte byte(42);

  // Ensure the total number of bits is 12 (8 data bits + 4 parity bits)
  EXPECT_EQ(byte.GetBits().size(), 12);
}

// Test ToInt() conversion
TEST(HammingByteTest, ConvertsToIntCorrectly) {
  HammingByte byte(42);
  EXPECT_EQ(byte.ToInt(), 42);
}

// Test validity check with a correct byte
TEST(HammingByteTest, ValidatesCorrectByte) {
  HammingByte byte(42);
  EXPECT_TRUE(byte.IsByteValid());
}

// Test error correction when one bit is flipped
TEST(HammingByteTest, CorrectsSingleBitError) {
  HammingByte byte(42);

  // Flip a single bit to introduce an error
  byte.ApplyNoise(3);

  // Should be able to self-correct
  EXPECT_TRUE(byte.IsByteValid());
}

// Test detection of uncorrectable multi-bit errors
TEST(HammingByteTest, DetectsUncorrectableErrors) {
  HammingByte byte(42);

  // Flip two bits, making it uncorrectable
  byte.ApplyNoise(3);
  byte.ApplyNoise(5);

  EXPECT_FALSE(byte.IsByteValid());
}

// Test equality operator
TEST(HammingByteTest, EqualityOperator) {
  HammingByte byte1(42);
  HammingByte byte2(42);
  HammingByte byte3(43);

  EXPECT_TRUE(byte1 == byte2);
  EXPECT_FALSE(byte1 == byte3);
}

// Test retransmission logic
TEST(HammingByteTest, ShouldRetransmit) {
  auto byte = std::make_shared<HammingByte>(42);
  TransmissionLog log(byte);

  // Initially, the byte should be valid and not require retransmission
  EXPECT_FALSE(byte->ShouldRetransmit(log));

  // Introduce an error to make it incorrect
  byte->ApplyNoise(3);

  // Now, retransmission should be needed
  EXPECT_TRUE(byte->ShouldRetransmit(log));
}
