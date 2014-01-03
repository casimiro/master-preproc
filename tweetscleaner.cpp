#include "tweetscleaner.h"
#include "utils.h"
#include <fstream>
#include <sstream>

namespace casimiro {

TweetsCleaner::TweetsCleaner(const DelafDict& _delafDict):
    m_delafDict(_delafDict)
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

void TweetsCleaner::cleanTweets(const std::string& _inFile, const std::string& _outFile) const
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
        
        auto nouns = m_delafDict.getNouns(words);
        auto unknownWords = m_delafDict.getUnknownWords(words);
        
        // tweetId creation_time userid retweet word1 word2 ... wordN
        output << fields.at(0) << " " << fields.at(2) << " " << fields.at(3) << " " << fields.at(4);
        for(auto word : nouns)
            output << " " << m_delafDict.getCanonical(word);
        for(auto word : unknownWords)
            output << " " << word;
        output << std::endl;
    }
}

}