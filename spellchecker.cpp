#include "spellchecker.h"
#include <iostream>

namespace casimiro {

SpellChecker::SpellChecker()
{
    prepareAspellConfiguration();
    
    AspellCanHaveError* possible_err = new_aspell_speller(s_spellConfig);
    if (aspell_error_number(possible_err) != 0)
        std::cout << aspell_error_message(possible_err) << std::endl;
    else
        m_speller = to_aspell_speller(possible_err);
}

SpellChecker::~SpellChecker()
{
    delete_aspell_speller(m_speller);
}

StringVector SpellChecker::getSuggestions(const StringVector& _words) const
{
    StringVector suggested;
    for(auto word : _words)
    {
        const AspellWordList* suggestions = aspell_speller_suggest(m_speller, word.c_str(), word.size());
        AspellStringEnumeration* elements = aspell_word_list_elements(suggestions);
        
        const char* suggestion;
        if((suggestion = aspell_string_enumeration_next(elements)) != nullptr)
            suggested.push_back(std::string(suggestion));
        
        delete_aspell_string_enumeration(elements);    
    }
    return suggested;
}

void SpellChecker::prepareAspellConfiguration()
{
    if(s_spellConfig == nullptr)
    {
        s_spellConfig = new_aspell_config();
        aspell_config_replace(s_spellConfig, "lang", "pt_BR");
        aspell_config_replace(s_spellConfig, "encoding", "utf-8");
        aspell_config_replace(s_spellConfig, "sug-mode", "ultra");
    }
}

}