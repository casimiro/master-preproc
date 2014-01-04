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
    virtual std::string getSuggestion(const std::string& _word) const;
    
    virtual void prepare();
    
private:
    AspellConfig* s_spellConfig = nullptr;
    AspellSpeller* m_speller = nullptr;
    
    void prepareAspellConfiguration();
};

}
#endif // SPELLCHECKER_H
