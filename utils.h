#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unicode/translit.h>

namespace casimiro {

UErrorCode status = U_ZERO_ERROR;
Transliterator* t = Transliterator::createInstance("NFD; [:M:] remove; NFC", UTRANS_FORWARD, status);

inline std::string ReplaceNonAsciiChars(const std::string& _dirty)
{
    std::string cleaned;
    auto uCleaned = UnicodeString::fromUTF8(_dirty.c_str());
    t->transliterate(uCleaned);
    uCleaned.toUTF8String<std::string>(cleaned);
    return cleaned;
}

}

#endif //UTILS_H