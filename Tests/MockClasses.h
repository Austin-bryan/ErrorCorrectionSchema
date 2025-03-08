#include "../Headers/Message/Byte.h"
#include "../Headers/Transmitter/TransmitterDestination.h"

class MockByte : public Byte {
private:
  int value;
public:
  explicit MockByte(int val) : Byte(val), value(val) {}

  bool operator==(const Byte& other) const override {
    return this->ToInt() == other.ToInt();
  }

  bool IsByteValid() override {
    return true;  // Always return valid for testing
  }

  void ComputeRedundancyBits() override {}

  int ToInt() const override { return value; }
};

class MockDestination : public TransmitterDestination {
public:
  void OnMessageReceive(Message& message) override {
    // Empty
  }
};
