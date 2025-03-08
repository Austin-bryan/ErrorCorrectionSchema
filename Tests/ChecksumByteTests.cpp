#include <gtest/gtest.h>
#include "../Headers/Message/ChecksumByte.h"
#include "../Headers/TransmissionLog.h"
#include "MockClasses.h"

// Test valid checksum computation
TEST(ChecksumByteTest, ComputesChecksumCorrectly) {
  ChecksumByte byte(42);
  int expectedChecksum = 0;

  // Manually compute expected checksum
  int sum = 0;
  for (int i = 0; i < 8; i++)
    sum += byte.GetBits()[i];

  expectedChecksum = sum % 2;

  EXPECT_EQ(byte.GetCheckSum(), expectedChecksum);
}

// Test ToInt() function
TEST(ChecksumByteTest, ConvertsToIntCorrectly) {
  ChecksumByte byte(42);
  EXPECT_EQ(byte.ToInt(), 42);
}

// Test ACK bit flipping
TEST(ChecksumByteTest, AcknowledgeFlipsBits) {
  ChecksumByte byte(42);
  int initialAck = byte.GetAck();
  int initialChecksum = byte.GetCheckSum();

  byte.Acknowledge();

  EXPECT_NE(byte.GetAck(), initialAck);
  EXPECT_NE(byte.GetCheckSum(), initialChecksum);
}

// Test byte validity check
TEST(ChecksumByteTest, ValidatesCorrectByte) {
  ChecksumByte byte(42);
  EXPECT_TRUE(byte.IsByteValid());
}

// Test checksum validation failure case
TEST(ChecksumByteTest, DetectsInvalidByte) {
  ChecksumByte byte(42);

  // Manually flip a bit to make it invalid
  byte.ApplyNoise(2);

  EXPECT_FALSE(byte.IsByteValid());
}

// Test retransmission logic
TEST(ChecksumByteTest, ShouldRetransmit) {
  auto byte = std::make_shared<ChecksumByte>(42);
  TransmissionLog log(byte);

  // Initially, the byte should be valid and not require retransmission
  EXPECT_FALSE(byte->ShouldRetransmit(log));

  // Introduce an error to make the checksum incorrect
  byte->ApplyNoise(3);

  // Now, retransmission should be needed
  EXPECT_TRUE(byte->ShouldRetransmit(log));
}

// Test equality operator
TEST(ChecksumByteTest, EqualityOperator) {
  ChecksumByte byte1(42);
  ChecksumByte byte2(42);
  ChecksumByte byte3(43);

  EXPECT_TRUE(byte1 == byte2);
  EXPECT_FALSE(byte1 == byte3);
}
