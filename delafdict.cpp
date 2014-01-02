#include "delafdict.h"
#include <fstream>
#include <iostream>
#include "utils.h"

namespace casimiro {

DelafDict::DelafDict()
{
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
        
        m_words.insert(std::make_pair(word, canonical));
    }
}

bool DelafDict::hasWord(const std::string& _word) const
{
    return (m_words.find(_word) != m_words.end());
}

std::string DelafDict::getCanonical(const std::string& _word) const
{
    auto it = m_words.find(_word);
    return it->second;
}

}
