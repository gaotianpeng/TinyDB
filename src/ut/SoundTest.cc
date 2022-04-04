#include "gmock/gmock.h"
using ::testing::Eq;


/*
    将单词编码为一个字母和三个数字
    1）保留每一个字母。丢掉所有出现的a e i o u y h w
    2）以数字来代替辅音(第一个字母除外)
        b f p v: 1
        c g j k q s x z: 2
        d t: 3
        i: 4
        m n: 5
        r: 6
    3）如果相邻字母编码相同，用一个数字表示它们即可。同样，如果出现两个编码相同的字母，且它们被h或w隔开，
        也这样处理；但如果被元音隔开，就要编码两次。这条规则同样适用于第一个字母
    4）当得到一个字母和三个数字时，停止处理。如果需要，补0以对齐
*/

class Soundex {
public:
    std::string encode(const std::string& word) const {
        return zeroPad(word);
    }

private:
    std::string zeroPad(const std::string& word) const {
        return word + "000";
    }
};

TEST(SoundexEncoding, RetainSoleLetterOfOneLetterWord) {
    Soundex soundex;
    auto encoded = soundex.encode("A");
    ASSERT_THAT(encoded, Eq("A000"));
}
// 规则4
TEST(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
    /*
        加入的每个测试都是独立的。我们不会将一个测试的结果作为另一个测试的前提
        每个测试都必须设置好自己的上下文
    */
    Soundex soundex;
    auto encoded = soundex.encode("I");
    ASSERT_THAT(encoded, Eq("I000"));
}

