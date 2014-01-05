#include <iostream>
#include "spellchecker.h"
#include "tweetscleaner.h"
#include <fstream>
#include <boost/concept_check.hpp>

using namespace casimiro;

StringUnorderedSet LoadDictFromFile(const std::string& _fileName)
{
    StringUnorderedSet dict;
    std::ifstream file(_fileName);
    std::string line;
    while(std::getline(file, line))
        dict.insert(line);
    return dict;
}

void cleanTweetsGroupingByUser(SpellChecker& speller, StringUnorderedSets& foreignDicts, DelafDict& DelafDict, TweetsCleaner& cleaner)
{
    bool spelling = false;
    int minChoosenWords = 30;
    double maxUnknownWordsRate = 0.3;
    
    cleaner.cleanTweetsGroupingByUser("/home/casimiro/tweet_sorted_dump", "data/tweets_cleaned_dump_grouped_by_user", spelling, minChoosenWords, maxUnknownWordsRate);
}

void cleanTweets(SpellChecker& speller, StringUnorderedSets& foreignDicts, DelafDict& DelafDict, TweetsCleaner& cleaner)
{
    bool spelling = false;
    int minChoosenWords = 4;
    double maxUnknownWordsRate = 0.5;
    
    cleaner.cleanTweets("/home/casimiro/tweet_sorted_dump", "data/tweets_cleaned_dump_grouped_by_user", spelling, minChoosenWords, maxUnknownWordsRate);
}

int main(int argc, char **argv) {
    SpellChecker speller;
    speller.prepare();
    
    StringUnorderedSets foreignDicts;
    //foreignDicts.push_back(LoadDictFromFile("data/en.dict"));
    //foreignDicts.push_back(LoadDictFromFile("data/es.dict"));
    
    DelafDict delafDict;
    delafDict.loadFromFile("data/delaf.dict");
    
    auto cleaner = TweetsCleaner(delafDict, foreignDicts, speller);
    
    cleanTweetsGroupingByUser(speller, foreignDicts, delafDict, cleaner);
    
    return 0;
}
