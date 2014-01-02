#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <vector>
#include <string>
#include <aspell.h>

namespace casimiro {

typedef std::vector<std::string> StringVector;
    
class SpellChecker
{
public:
    SpellChecker();
    virtual ~SpellChecker();
    
    virtual StringVector getSuggestions(const StringVector& _words) const;
    
private:
    AspellConfig* s_spellConfig;
    void prepareAspellConfiguration();
    
    AspellSpeller* m_speller;
};

}
#endif // SPELLCHECKER_H
