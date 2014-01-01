#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unicode/translit.h>
#include <unicode/regex.h>

namespace casimiro {

UErrorCode status = U_ZERO_ERROR;
Transliterator* TRANSLITERATOR = Transliterator::createInstance("NFD; [:M:] remove; NFC", UTRANS_FORWARD, status);

RegexMatcher* LAUGH_MATCHER = new RegexMatcher("(\\b[hua]+\\b)|(\\b[he]+\\b)|(\\b[rs]+\\b)|(\\b[Kk]+\\b)", 0, status);
RegexMatcher* URL_MATCHER = new RegexMatcher("https?://[\\.\\w/?]*", 0, status);

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
}

#endif //UTILS_H