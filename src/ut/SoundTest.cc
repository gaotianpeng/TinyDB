#include "gmock/gmock.h"

/*
    {测试用例名称, 测试的描述性名称}
    测试用例(test case): 是一些能共享数据和子程序的测试集合
*/

class Soundex {
public:
    std::string encode(const std::string& word) const {
        return "A";
    }
};

TEST(SoundexEncoding, RetainSoleLetterOfOneLetterWord) {
    Soundex soundex;
    auto encoded = soundex.encode("A");
    ASSERT_THAT(encoded, testing::Eq("A"));
}