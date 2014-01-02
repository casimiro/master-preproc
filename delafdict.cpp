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
        auto word = line.substr(0,commaPos);
        m_words.insert(ReplaceNonAsciiChars(word));
    }
}

bool DelafDict::hasWord(const std::string &_word)
{
    return (m_words.find(_word) != m_words.end());
}

}
