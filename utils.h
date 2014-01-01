#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unicode/translit.h>
#include <unicode/regex.h>

namespace casimiro {

typedef std::vector<std::string> StringVector;

UErrorCode status = U_ZERO_ERROR;
Transliterator* TRANSLITERATOR = Transliterator::createInstance("NFD; [:M:] remove; NFC", UTRANS_FORWARD, status);

RegexMatcher* LAUGH_MATCHER = new RegexMatcher("(\\b[hua]+\\b)|(\\b[he]+\\b)|(\\b[rs]+\\b)|(\\b[Kk]+\\b)", 0, status);
RegexMatcher* URL_MATCHER = new RegexMatcher("https?://[\\.\\w/?]*", 0, status);
RegexMatcher* MENTION_MATCHER = new RegexMatcher("@[\\w]{2,}\\b", 0, status);
RegexMatcher* WORD_MATCHER = new RegexMatcher("\\b\\p{L}{2,}\\b", 0, status);
RegexMatcher* STOP_WORDS_MATCHER = new RegexMatcher("(\\b[dt][aeo]\\b)|(\\bvc\\b)|(\\brt\\b)", 0, status);

inline std::string ReplaceNonAsciiChars(const std::string& _dirty)
{
    std::string cleaned;
    auto uCleaned = UnicodeString::fromUTF8(_dirty.c_str());
    TRANSLITERATOR->transliterate(uCleaned);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

inline std::string RemoveLaughs(const std::string& _dirty)
{
    std::string cleaned;
    auto uDirty = UnicodeString::fromUTF8(_dirty.c_str());
    LAUGH_MATCHER->reset(uDirty);
    auto uCleaned = LAUGH_MATCHER->replaceAll("", status);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

inline std::string RemoveURLs(const std::string& _dirty)
{
    std::string cleaned;
    auto uDirty = UnicodeString::fromUTF8(_dirty.c_str());
    URL_MATCHER->reset(uDirty);
    auto uCleaned = URL_MATCHER->replaceAll("", status);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

inline std::string RemoveMentions(const std::string& _dirty)
{
    std::string cleaned;
    auto uDirty = UnicodeString::fromUTF8(_dirty.c_str());
    MENTION_MATCHER->reset(uDirty);
    auto uCleaned = MENTION_MATCHER->replaceAll("", status);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

inline std::string RemoveStopWords(const std::string& _dirty)
{
    std::string cleaned;
    auto uDirty = UnicodeString::fromUTF8(_dirty.c_str());
    STOP_WORDS_MATCHER->reset(uDirty);
    auto uCleaned = STOP_WORDS_MATCHER->replaceAll("", status);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

inline StringVector GetWordsFromText(const std::string& _text)
{
    StringVector words;
    auto cleaned = ReplaceNonAsciiChars(_text);
    cleaned = RemoveLaughs(cleaned);
    cleaned = RemoveURLs(cleaned);
    cleaned = RemoveMentions(cleaned);

    auto uText = UnicodeString::fromUTF8(cleaned.c_str());
    WORD_MATCHER->reset(uText);
    while(WORD_MATCHER->find())
    {
        std::string aux;
        auto group = WORD_MATCHER->group(status);
        group.toLower();
        group.toUTF8String<std::string>(aux);
        words.push_back(aux);
    }

    return words;
}

}

#endif //UTILS_H
