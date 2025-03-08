#include <gtest/gtest.h>
#include "../Headers/Message/TripledByte.h"
#include "../Headers/TransmissionLog.h"
#include "MockClasses.h"

// Test constructor initializes bits correctly
TEST(TripledByteTest, ConstructorInitializesBitsCorrectly) {
  TripledByte byte(42);

  // Ensure the total number of bits is tripled (8 data bits * 3 = 24 bits)
  EXPECT_EQ(byte.GetBits().size(), 24);
}

// Test ToInt() conversion
TEST(TripledByteTest, ConvertsToIntCorrectly) {
  TripledByte byte(42);
  EXPECT_EQ(byte.ToInt(), 42);
}

// Test bit consolidation function
TEST(TripledByteTest, ConsolidatesBitsCorrectly) {
  TripledByte byte(42);

  // Directly test the private bit consolidation logic via a helper function
  std::vector<int> tripledBits = { 0, 0, 0, 1, 1, 1, 1, 0, 1 };
  std::vector<int> expectedConsolidated = { 0, 1, 1 };

  EXPECT_EQ(byte.ConsolidateBits(tripledBits), expectedConsolidated);
}

// Test validity check with a correct byte
TEST(TripledByteTest, ValidatesCorrectByte) {
  TripledByte byte(42);
  EXPECT_TRUE(byte.IsByteValid());
}

// Test correction of a single-bit error
TEST(TripledByteTest, CorrectsSingleBitError) {
  TripledByte byte(42);

  // Introduce an error by flipping a single bit
  byte.ApplyNoise(3);

  // The redundancy should correct it
  EXPECT_TRUE(byte.IsByteValid());
}

// Test equality operator
TEST(TripledByteTest, EqualityOperator) {
  TripledByte byte1(42);
  TripledByte byte2(42);
  TripledByte byte3(43);

  EXPECT_TRUE(byte1 == byte2);
  EXPECT_FALSE(byte1 == byte3);
}

// Test retransmission logic
TEST(TripledByteTest, ShouldRetransmit) {
  auto byte = std::make_shared<TripledByte>(42);
  TransmissionLog log(byte);

  // Initially, the byte should be valid and not require retransmission
  EXPECT_FALSE(byte->ShouldRetransmit(log));

  // Introduce multiple errors to make it incorrect
  byte->ApplyNoise(1);
  byte->ApplyNoise(2);

  // Now, retransmission should be needed
  EXPECT_TRUE(byte->ShouldRetransmit(log));
}