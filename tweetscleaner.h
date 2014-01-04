#ifndef TWEETSCLEANER_H
#define TWEETSCLEANER_H

#include <unordered_set>
#include <string>
#include "delafdict.h"
#include "spellchecker.h"

namespace casimiro {

typedef std::unordered_set<std::string> StringUnorderedSet;
typedef std::vector<StringUnorderedSet> StringUnorderedSets;

class TweetsCleaner
{
public:
    TweetsCleaner(const DelafDict& _delafDict, const StringUnorderedSets& _foreignDicts, const SpellChecker& _speller);
    virtual ~TweetsCleaner();
    
    virtual void cleanTweets(const std::string& _inFile, const std::string& _outFile, bool _spelling, int _minChoosenWords = 0, double _maxUnknownWordsRate = 0) const;
    
    virtual StringVector chooseWords(const StringVector& _words, bool _spelling = false, double* _unknownWordsRateRet = nullptr) const;
    
private:
    const DelafDict& m_delafDict;
    const StringUnorderedSets& m_foreignDicts;
    const SpellChecker& m_speller;
    
    virtual bool isForeignWord(const std::string& _word) const;
    
    virtual void writeOutput(std::ofstream& _output, const StringVector& _fields, const StringVector& _words) const;
};

}
#endif // TWEETSCLEANER_H
