#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unicode/translit.h>

namespace casimiro {

inline std::string ReplaceNonAsciiChars(const std::string& _dirty)
{
    std::string cleaned;
    UErrorCode status = U_ZERO_ERROR;
    auto uCleaned = UnicodeString::fromUTF8(_dirty.c_str());
    auto t = Transliterator::createInstance("NFD; [:M:] remove; NFC", UTRANS_FORWARD, status);
    t->transliterate(uCleaned);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

}

#endif //UTILS_H