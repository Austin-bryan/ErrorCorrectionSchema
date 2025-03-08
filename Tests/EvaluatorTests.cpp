#include "../pch.h"
#include <gtest/gtest.h>
#include <sstream>
#include "../Headers/Evaluator.h"
#include "../Headers/TransmissionLog.h"
#include "MockClasses.h"

class EvaluatorTest : public ::testing::Test {
public:
  static void PushBackLogs(const TransmissionLog& log1, const TransmissionLog& log2) {
    Evaluator::logs.push_back(log1);
    Evaluator::logs.push_back(log2);
  }
protected:
  std::stringstream buffer;
  std::streambuf* oldCout;

  void SetUp() override {
    // Redirect cout to capture printed output
    Evaluator::logs.clear();
    oldCout = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
  }

  void TearDown() override {
    // Restore cout
    std::cout.rdbuf(oldCout);
  }
};

TEST_F(EvaluatorTest, EvaluatesBasicStatsCorrectly) {
  // Setup test logs
  Evaluator::Percentage     = 10.0;
  Evaluator::IterationCount = 5;
  Evaluator::ByteMethod     = "Hamming";

  auto byte1 = std::make_shared<MockByte>(42);
  auto byte2 = std::make_shared<MockByte>(43);

  TransmissionLog log1(byte1);
  TransmissionLog log2(byte2);

  log1.CountTransmission();
  log2.CountTransmission();
  log2.CountTransmission();
  log2.Verify(byte1);  // Incorrect verification

  EvaluatorTest::PushBackLogs(log1, log2);

  // Call function
  Evaluator::Evaluate();

  // Check output contains expected values
  std::string output = buffer.str();
  EXPECT_NE(output.find("* Error Percentage: 10%"), std::string::npos);
  EXPECT_NE(output.find("* Iteration count: 5"), std::string::npos);
  EXPECT_NE(output.find("* Byte method: Hamming"), std::string::npos);
  EXPECT_NE(output.find("* Incorrect: 1, Correct: 1"), std::string::npos);
}

TEST_F(EvaluatorTest, HandlesEmptyLogGracefully) {
  Evaluator::Evaluate();

  std::string output = buffer.str();
  EXPECT_NE(output.find("* Incorrect: 0, Correct: 0"), std::string::npos);
}