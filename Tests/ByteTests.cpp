#include <gtest/gtest.h>
#include "../Headers/TransmissionLog.h"
#include "../Headers/Message/Byte.h"
#include "MockClasses.h"

// Test Byte Constructor for valid input
TEST(ByteTest, ConstructorValidInput) {
  MockByte byte(42); // 42 = 00101010 in binary

  // Expected bit pattern for 42 (00101010)
  std::vector<int> expectedBits = { 0, 0, 1, 0, 1, 0, 1, 0 };

  EXPECT_EQ(byte.GetBits(), expectedBits);
}

// Test Byte Constructor for invalid input (throws exception)
TEST(ByteTest, ConstructorInvalidInput) {
  EXPECT_THROW(MockByte(-1), std::invalid_argument);
  EXPECT_THROW(MockByte(256), std::invalid_argument);
}

// Test Copy Constructor
TEST(ByteTest, CopyConstructor) {
  MockByte byte1(42);
  MockByte byte2(byte1);

  EXPECT_EQ(byte1.GetBits(), byte2.GetBits());
}

// Test Copy Assignment
TEST(ByteTest, CopyAssignment) {
  MockByte byte1(42);
  MockByte byte2(100);  // Different byte initially

  byte2 = byte1;  // Assign byte1 to byte2

  EXPECT_EQ(byte1.GetBits(), byte2.GetBits());
}

// Test Move Constructor
TEST(ByteTest, MoveConstructor) {
  MockByte byte1(42);
  MockByte byte2(std::move(byte1));  // Move byte1 into byte2

  // byte1 is in a moved state, but byte2 should retain correct data
  EXPECT_EQ(byte2.ToInt(), 42);
}

// Test Move Assignment
TEST(ByteTest, MoveAssignment) {
  MockByte byte1(42);
  MockByte byte2(100);

  byte2 = std::move(byte1);

  EXPECT_EQ(byte2.ToInt(), 42);
}

// Test ApplyNoise
TEST(ByteTest, ApplyNoise) {
  MockByte byte(42);
  TransmissionLog log(std::make_shared<MockByte>(42));

  byte.ApplyNoise(2);  // Flip the 3rd bit (0-based index)

  EXPECT_NE(byte.ToInt(), 42);  // Byte should have changed
}

// Test ShouldRetransmit (Valid Case)
TEST(ByteTest, ShouldRetransmit_Valid) {
  auto byte = std::make_shared<MockByte>(42);
  TransmissionLog log(byte);

  EXPECT_FALSE(byte->ShouldRetransmit(log));  // Should return false if byte is valid
}

// Test ShouldRetransmit (Invalid Case)
class InvalidByte : public MockByte {
public:
  InvalidByte(int number) : MockByte(number) {}
  bool IsByteValid() override { return false; }  // Simulate an invalid byte
  void ComputeRedundancyBits() override {}
  int ToInt() const override { return 0; }
};

TEST(ByteTest, ShouldRetransmit_Invalid) {
  auto byte = std::make_shared<InvalidByte>(42);
  TransmissionLog log(byte);

  EXPECT_TRUE(byte->ShouldRetransmit(log));  // Should return true if byte is invalid
}

// Test Output Operator
TEST(ByteTest, OutputOperator) {
  MockByte byte(42);
  std::ostringstream output;
  output << &byte;

  std::string expectedOutput = "42 (00101010 )";  // Expected output format
  EXPECT_EQ(output.str(), expectedOutput);
}
