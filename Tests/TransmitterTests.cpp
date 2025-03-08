#include <gtest/gtest.h>
#include "../Headers/Transmitter/Transmitter.h"
#include "../Headers/Message/Message.h"
#include "../Headers/NoisyChannel.h"
#include "MockClasses.h"

// Mock NoisyChannel for controlled behavior
class MockNoisyChannel {
public:
  static void ApplyNoise(const std::shared_ptr<Byte>& byte, TransmissionLog& log) {
    // Simulate applying noise, but do nothing in the mock
  }
};

// Test Fixture
class TransmitterTest : public ::testing::Test {
protected:
  Transmitter transmitter;
  std::shared_ptr<MockDestination> mockDestination = std::make_shared<MockDestination>();
  std::shared_ptr<MockByte> mockByte = std::make_shared<MockByte>(42);
};

// Ensures transmission count increases after sending
TEST_F(TransmitterTest, IncrementsTransmissionCount) {
  TransmissionLog log(mockByte);
  Message message{ mockDestination, mockByte, log };

  int initialCount = log.GetTransmissionCount();

  transmitter.Send(message);

  EXPECT_EQ(log.GetTransmissionCount(), initialCount + 1);
}
