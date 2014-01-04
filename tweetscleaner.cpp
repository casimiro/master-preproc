#include "tweetscleaner.h"
#include "utils.h"
#include <fstream>
#include <sstream>

namespace casimiro {

TweetsCleaner::TweetsCleaner(const DelafDict& _delafDict, const StringUnorderedSets& _foreignDicts, const SpellChecker& _speller):
    m_delafDict(_delafDict),
    m_foreignDicts(_foreignDicts),
    m_speller(_speller)
{
}

TweetsCleaner::~TweetsCleaner()
{

}

StringVector splitString(const std::string& _str, char _delim)
{
    StringVector items;
    std::stringstream ss(_str);
    std::string item;
    while(std::getline(ss, item, _delim))
        items.push_back(item);
    return items;
}

bool TweetsCleaner::isForeignWord(const std::string& _word) const
{
    bool foreign = false;
    for(auto dict : m_foreignDicts)
    {
        if(dict.find(_word) != dict.end())
        {
            foreign = true;
            break;
        }
    }
    return foreign;
}

StringVector TweetsCleaner::chooseWords(const casimiro::StringVector& _words) const
{
    StringVector choosen;
    auto nouns = m_delafDict.getNouns(_words);
    auto unknownWords = m_delafDict.getUnknownWords(_words);
    
    for(auto word : nouns)
        choosen.push_back(m_delafDict.getCanonical(word));
    
    for(auto word : unknownWords)
    {
        if(!isForeignWord(word))
        {
            auto suggestion = m_speller.getSuggestion(word);
            if(suggestion.empty())
                choosen.push_back(word);
            else
                choosen.push_back(suggestion);
        }
    }
    return choosen;
}

void TweetsCleaner::writeOutput(std::ofstream& _output, const StringVector& _fields, const StringVector& _words) const
{
    // tweetId creation_time userid retweet word1 word2 ... wordN
    _output << _fields.at(0) << " " << _fields.at(2) << " " << _fields.at(3) << " " << _fields.at(4);
    
    for(auto word : _words)
        _output << " " << word;
    _output << std::endl;
}

void TweetsCleaner::cleanTweets(const std::string& _inFile, const std::string& _outFile, int _minChoosenWords) const
{
    std::ifstream input(_inFile);
    std::ofstream output(_outFile);
    std::string line;
    while(std::getline(input, line))
    {
        StringVector fields = splitString(line, '\t');
        auto words = GetWordsFromText(fields.at(1));
        if(words.size() == 0)
            continue;
        
        auto choosen = chooseWords(words);
        
        if(_minChoosenWords > 0 && choosen.size() < _minChoosenWords)
            continue;
        
        writeOutput(output, fields, choosen);
    }
}

}