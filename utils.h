#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unicode/translit.h>
#include <unicode/regex.h>
#include <vector>

namespace casimiro {

typedef std::vector<std::string> StringVector;

extern UErrorCode status;
extern Transliterator* TRANSLITERATOR;

extern RegexMatcher* LAUGH_MATCHER;
extern RegexMatcher* LINE_BREAK_TAB_MATCHER;
extern RegexMatcher* SMILEYS_MATCHER;
extern RegexMatcher* URL_MATCHER;
extern RegexMatcher* MENTION_MATCHER;
extern RegexMatcher* WORD_MATCHER;
extern RegexMatcher* STOP_WORDS_MATCHER;

inline std::string ReplaceNonAsciiChars(const std::string& _dirty)
{
    std::string cleaned;
    auto uCleaned = UnicodeString::fromUTF8(_dirty.c_str());
    TRANSLITERATOR->transliterate(uCleaned);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

inline std::string RemoveLineBreakAndTabulations(const std::string& _dirty)
{
    std::string cleaned;
    auto uDirty = UnicodeString::fromUTF8(_dirty.c_str());
    LINE_BREAK_TAB_MATCHER->reset(uDirty);
    auto uCleaned = LINE_BREAK_TAB_MATCHER->replaceAll(" ", status);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

inline std::string RemoveSmileys(const std::string& _dirty)
{
    std::string cleaned;
    auto uDirty = UnicodeString::fromUTF8(_dirty.c_str());
    SMILEYS_MATCHER->reset(uDirty);
    auto uCleaned = SMILEYS_MATCHER->replaceAll("", status);
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
    cleaned = RemoveSmileys(cleaned);
    cleaned = RemoveLineBreakAndTabulations(cleaned);
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
