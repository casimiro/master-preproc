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
    
    if(type == std::string("N") || type == std::string("N+Pr"))
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
        
        auto it = m_words.find(word);
        if(it != m_words.end())
            if(it->second.wordType != Noun)
                m_words.erase(it);
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

StringVector DelafDict::getUnknownWords(const StringVector& _words) const
{
    StringVector unknownWords;
    for(auto word : _words)
        if(!hasWord(word))
            unknownWords.push_back(word);

    return unknownWords;
}

StringVector DelafDict::getNouns(const StringVector& _words) const
{
    StringVector nouns;
    for(auto word : _words)
    {
        if(!hasWord(word))
            continue;
        
        auto wordType = getWordType(word);
        if(wordType == Noun || wordType == Abbreviation || wordType == Acronym)
            nouns.push_back(word);
    }
    return nouns;
}

bool DelafDict::isNoun(const std::string& _word) const
{
    if(hasWord(_word) && m_words.find(_word)->second.wordType == Noun)
        return true;
    return false;
}

}
