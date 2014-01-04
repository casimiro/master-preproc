#include "spellchecker.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "utils.h"

namespace casimiro {

SpellChecker::SpellChecker()
{
}

void SpellChecker::prepare()
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
    if(m_speller != nullptr)
        delete_aspell_speller(m_speller);
}

std::string SpellChecker::getSuggestion(const std::string& _word) const
{
    if(m_speller == nullptr)
        throw std::runtime_error("Unprepared speller. Please prepare it before using it by calling prepare()");
    
    auto suggested = std::string();
    
    const AspellWordList* suggestions = aspell_speller_suggest(m_speller, _word.c_str(), _word.size());
    AspellStringEnumeration* elements = aspell_word_list_elements(suggestions);
    
    const char* suggestion;
    if((suggestion = aspell_string_enumeration_next(elements)) != nullptr)
    {
        suggested = std::string(suggestion);
        std::transform(suggested.begin(), suggested.begin()+1, suggested.begin(), tolower);
        suggested = ReplaceNonAsciiChars(suggested);
    }
    
    delete_aspell_string_enumeration(elements);
    return suggested;
}

StringVector SpellChecker::getSuggestions(const casimiro::StringVector& _words) const
{
    if(m_speller == nullptr)
        throw std::runtime_error("Unprepared speller. Please prepare it before using it by calling prepare()");
    
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