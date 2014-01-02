#include "utils.h"

namespace casimiro {

UErrorCode status = U_ZERO_ERROR;
Transliterator* TRANSLITERATOR = Transliterator::createInstance("NFD; [:M:] remove; NFC", UTRANS_FORWARD, status);

RegexMatcher* LAUGH_MATCHER = new RegexMatcher("(\\b[hua]+\\b)|(\\b[he]+\\b)|(\\b[rs]+\\b)|(\\b[Kk]+\\b)", 0, status);
RegexMatcher* URL_MATCHER = new RegexMatcher("https?://[\\.\\w/?]*", 0, status);
RegexMatcher* MENTION_MATCHER = new RegexMatcher("@[\\w]{2,}\\b", 0, status);
RegexMatcher* WORD_MATCHER = new RegexMatcher("\\b\\p{L}{2,}\\b", 0, status);
RegexMatcher* STOP_WORDS_MATCHER = new RegexMatcher("(\\b[dt][aeo]\\b)|(\\bvc\\b)|(\\brt\\b)", 0, status);

}
