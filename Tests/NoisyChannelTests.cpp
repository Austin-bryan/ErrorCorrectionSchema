#include "../pch.h"
#include <gtest/gtest.h>
#include "../Headers/NoisyChannel.h"
#include "../Headers/TransmissionLog.h"
#include "MockClasses.h"

TEST(NoisyChannelTest, NoNoiseAppliedWhenPercentageIsZero) {
  NoisyChannel::NoisePercentage = 0.0; // No noise should be applied

  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);

  NoisyChannel::ApplyNoise(byte, log);

  EXPECT_EQ(log.GetNoiseCount(), 0); // Ensure no noise was applied
}

TEST(NoisyChannelTest, NoiseAppliedAtHighPercentage) {
  NoisyChannel::NoisePercentage = 100.0; // Almost guaranteed noise application

  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);

  NoisyChannel::ApplyNoise(byte, log);

  EXPECT_GT(log.GetNoiseCount(), 0); // Ensure at least one noise event happened
}

TEST(NoisyChannelTest, NoiseCanBeAppliedMultipleTimes) {
  NoisyChannel::NoisePercentage = 75.0; // High chance of multiple noise applications

  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);

  NoisyChannel::ApplyNoise(byte, log);

  EXPECT_GE(log.GetNoiseCount(), 1); // At least 1 noise event should have occurred
  EXPECT_LE(log.GetNoiseCount(), byte->Size()); // Cannot exceed byte size
}