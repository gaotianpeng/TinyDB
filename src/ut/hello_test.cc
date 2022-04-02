#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <map>
#include <utility>
using namespace std;

class MockFoo {
public:
	MOCK_METHOD((std::pair<bool, int>), GetPair, ());
	MOCK_METHOD(bool, CheckMap, ((std::map<int, double>), bool));
};


// TEST(HelloTest, BasicAssertions) {
// 	EXPECT_STRNE("hello", "world");
// 	EXPECT_EQ(7 * 6, 42);
// }

