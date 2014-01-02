#include "delafdict.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "utils.h"

namespace casimiro {

DelafDict::DelafDict()
{
}

WordType DelafDict::extractWordType(const std::string& _line)
{
    auto periodPos = _line.find_first_of(".");
    auto colonPos = _line.find_first_of(":");
    auto type = _line.substr(periodPos+1, (colonPos-periodPos-1));
    
    if(type == std::string("N"))
        return Noun;
    else if(type == std::string("A"))
        return Adjective;
    else if(type == std::string("ABREV"))
        return Abbreviation;
    else if(type == std::string("SIGL"))
        return Acronym;
    else
        return UnknownWordType;
}

void DelafDict::loadFromFile(const std::string &_fileName)
{
    std::ifstream file(_fileName);
    std::string line;
    while(std::getline(file, line))
    {
        auto commaPos = line.find_first_of(",");
        auto periodPos = line.find_first_of(".");
        auto word = ReplaceNonAsciiChars(line.substr(0,commaPos));
        auto canonical = ReplaceNonAsciiChars(line.substr(commaPos+1, (periodPos-commaPos-1)));
        
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        std::transform(canonical.begin(), canonical.end(), canonical.begin(), ::tolower);
        
        m_words.insert(std::make_pair(word, DelafWordInfo(canonical, extractWordType(line))));
    }
}

bool DelafDict::hasWord(const std::string& _word) const
{
    return (m_words.find(_word) != m_words.end());
}

std::string DelafDict::getCanonical(const std::string& _word) const
{
    auto it = m_words.find(_word);
    return it->second.canonical;
}

WordType DelafDict::getWordType(const std::string& _word) const
{
    auto it = m_words.find(_word);
    return it->second.wordType;
}

}
