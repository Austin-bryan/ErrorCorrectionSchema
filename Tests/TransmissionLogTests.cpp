
#include "../pch.h"
#include <gtest/gtest.h>
#include "../Headers/TransmissionLog.h"
#include "../Headers/Message/Byte.h"
#include "MockClasses.h"

// Test case to check if TransmissionLog initializes correctly
TEST(TransmissionLogTest, InitializesCorrectly) {
  auto byte = std::make_shared<MockByte>(42); // Test with number 42
  TransmissionLog log(byte);

  EXPECT_EQ(log.GetTransmissionCount(), 0);
  EXPECT_EQ(log.GetNoiseCount(), 0);
  EXPECT_EQ(log.GetVerification(), EVerification::Unverified);
}

// Test case to verify counting transmissions
TEST(TransmissionLogTest, CountsTransmissions) {
  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);

  log.CountTransmission();
  EXPECT_EQ(log.GetTransmissionCount(), 1);

  log.CountTransmission();
  EXPECT_EQ(log.GetTransmissionCount(), 2);
}

// Test case to verify noise count
TEST(TransmissionLogTest, TracksNoiseCorrectly) {
  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);

  log.CountNoise(3);  // Simulate bit flip at index 3
  EXPECT_EQ(log.GetNoiseCount(), 1);

  log.CountNoise(5);
  EXPECT_EQ(log.GetNoiseCount(), 2);
}

// Test verification process
TEST(TransmissionLogTest, VerifiesBytesCorrectly) {
  auto byte = std::make_shared<MockByte>(42);
  auto modifiedByte = std::make_shared<MockByte>(42); // No modification

  TransmissionLog log(byte);
  log.Verify(modifiedByte); // Should be correct

  EXPECT_EQ(log.GetVerification(), EVerification::Correct);

  // Test incorrect verification
  auto differentByte = std::make_shared<MockByte>(43); // Different value
  TransmissionLog log2(byte);
  log2.Verify(differentByte);

  EXPECT_EQ(log2.GetVerification(), EVerification::Incorrect);
}

TEST(TransmissionLogTest, ReturnsOriginalByte) {
  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);
  EXPECT_EQ(log.GetOriginalByte(), byte);
}

TEST(TransmissionLogTest, DetectsRetransmission) {
  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);
  EXPECT_FALSE(log.WasRetransmitted());
  log.CountTransmission();
  EXPECT_FALSE(log.WasRetransmitted());
  log.CountTransmission();
  EXPECT_TRUE(log.WasRetransmitted());
}

TEST(TransmissionLogTest, OutputsCorrectly) {
  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);

  std::ostringstream output, byteStr;
  output << log;
  byteStr << byte;

  std::string expected = "Original: " + byteStr.str() +
    ", Final: 0, Transmissions: 0, Noises: 0, Verification: Unverified\n";

  EXPECT_EQ(output.str(), expected);
}