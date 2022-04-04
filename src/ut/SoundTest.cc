#include "gmock/gmock.h"
#include "Soundex.h"
#include <iostream>
using namespace std;
using namespace testing;

// TEST(SoundexEncoding, RetainSoleLetterOfOneLetterWord) {
//     Soundex soundex;
//     auto encoded = soundex.encode("A");
//     ASSERT_THAT(encoded, Eq("A000"));
// }
// // 规则4
// TEST(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
//     /*
//         加入的每个测试都是独立的。我们不会将一个测试的结果作为另一个测试的前提
//         每个测试都必须设置好自己的上下文
//     */
//     Soundex soundex;
//     auto encoded = soundex.encode("I");
//     ASSERT_THAT(encoded, Eq("I000"));
// }

/*
    相关测试拥有一些共同的代码是常见的
    gmock 允许我们定义一个fixture类,我们可以在这个类中为相关的测试声明函数和数据
    gmock 会在运行每个测试时创建 fixture 类实例
*/

class SoundexEncoding: public testing::Test {
public:
    SoundexEncoding() {
        // cout << "this: " << this << endl;
    }
    Soundex soundex;
};

// TEST_F, F表示fixture
TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
    ASSERT_THAT(soundex.encode("A"), Eq("A000"));
    ASSERT_THAT(soundex.encode("Ab"), Eq("A100"));
}

// 规则4
TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
    ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

// 规则2：在第一个字母后，用数字替换辅音
// TEST_F(SoundexEncoding, RetainsSole)

// EXPECT_THAT 希望一个断言失败时，其他的代码能继续执行
TEST_F(SoundexEncoding, ReplaceConsonantsWithAppropriateDigits) {
    EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
    EXPECT_THAT(soundex.encode("Ac"), Eq("A200"));
    EXPECT_THAT(soundex.encode("Ad"), Eq("A300"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics) {
    ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}

// TEST_F(SoundexEncoding, DISABLED_ReplacesMultipleConsonantsWithDigits) {
TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits) {
    ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

// 规则4：声明Soundex编码结果必须是4个字符
// --gtest_catch_exceptions=0
TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
    ASSERT_THAT(soundex.encode("Dcdlb").length(), Eq(4u));
}

// 规则1：要丢掉所有元音以及w h y
TEST_F(SoundexEncoding, IgnoresVowelLikeLetters) {
    ASSERT_THAT(soundex.encode("Baeiouhycdl"), Eq("B234"));
    ASSERT_THAT(soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234"));
}

// 处理两个相邻字母有相同数字编码的情形
TEST_F(SoundexEncoding, CombinesDuplicateEncodings) {
    ASSERT_THAT(soundex.encodedDigit('b'), Eq(soundex.encodedDigit('f')));
    ASSERT_THAT(soundex.encodedDigit('c'), Eq(soundex.encodedDigit('g')));
    ASSERT_THAT(soundex.encodedDigit('d'), Eq(soundex.encodedDigit('t')));

    ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UppercasesFirstLetter) {
    ASSERT_THAT(soundex.encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants) {
    ASSERT_THAT(soundex.encode("BCDL"), Eq(soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st) {
    ASSERT_THAT(soundex.encode("Bbcd"), Eq("B230"));
}