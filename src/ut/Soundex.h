#ifndef __UT_SOUNDEX_H
#define __UT_SOUNDEX_H
#include <string>
#include <unordered_map>
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
        return zeroPad(upperFront(head(word)) + tail(encodedDigits(word)));
    }

    std::string encodedDigit(char letter) const {
        const std::unordered_map<char, std::string> encodings {
            {'b', "1"}, {'f', "1"}, {'p', "1"},{'v', "1"},
            {'c', "2"}, {'g', "2"}, {'j', "2"},{'k', "2"}, {'q', "2"}, 
            {'d', "3"}, {'t', "3"},
            {'l', "4"},
            {'m', "5"}, {'n', "5"},
            {'r', "6"}
        };

        auto it = encodings.find(lower(letter));
        return it == encodings.end() ? NotADigit : it->second;
    }

private:
    std::string upperFront(const std::string& string) const {
        return std::string(1, std::toupper(static_cast<unsigned char>(string.front())));
    }

    std::string head(const std::string& word) const {
        return word.substr(0, 1);
    }

    std::string encodedDigits(const std::string& word) const {
        std::string encoding;
        encodeHead(encoding, word);
        encodeTail(encoding, word);
        return encoding;
    }
    
    void encodeHead(std::string& encoding, const std::string& word) const {
        encoding += encodedDigit(word.front());
    }

    void encodeTail(std::string& encoding, const std::string& word) const {
        for (auto i = 1u; i < word.length(); i++) {
            if (!isComplete(encoding)) {
                encodeLetter(encoding, word[i], word[i-1]);
            }
        }
    }

    void encodeLetter(std::string& encoding, char letter, char lastLetter) const {
        auto digit = encodedDigit(letter);
        if (digit != NotADigit && (digit != lastDigit(encoding) || isVowel(lastLetter))) {
            encoding += digit;
        }
    }

    bool isVowel(char letter) const {
        return std::string("aeiouy").find(lower(letter)) != std::string::npos;
    }

    std::string lastDigit(const std::string& encoding) const {
        if (encoding.empty()) {
            return NotADigit;
        }
        return std::string(1, encoding.back());
    }

    bool isComplete(const std::string& encoding) const {
        return encoding.length() == MaxCodeLength;
    }

    std::string tail(const std::string& word) const {
        return word.substr(1);
    }

    std::string zeroPad(const std::string& word) const {
        auto zerosNeeded = MaxCodeLength - word.length();
        return word + std::string(zerosNeeded, '0');
    }

    char lower(char c) const {
        return std::tolower(static_cast<unsigned char>(c));
    }

    static const size_t MaxCodeLength {4};
    const std::string NotADigit{"*"};
};

#endif // __UT_SOUNDEX_H