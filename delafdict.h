#ifndef DELAFDICT_H
#define DELAFDICT_H

#include <string>
#include <map>
#include <vector>

namespace casimiro {

typedef std::vector<std::string> StringVector;

enum WordType {
    Noun,
    Adjective,
    Abbreviation,
    Acronym,
    UnknownWordType
};

class DelafWordInfo {
public:
    DelafWordInfo(const std::string _canonical, WordType _wordType):canonical(_canonical), wordType(_wordType)
    {}
    std::string canonical;
    WordType wordType;
};

class DelafDict
{
public:
    DelafDict();

    virtual void loadFromFile(const std::string& _fileName);

    virtual bool hasWord(const std::string& _word) const;
    
    virtual std::string getCanonical(const std::string& _word) const;
    
    virtual WordType getWordType(const std::string& _word) const;
    
    virtual StringVector getUnknownWords(const StringVector& _words) const;

private:
    std::map<std::string, DelafWordInfo> m_words;
    
    virtual WordType extractWordType(const std::string& _line);
};

}


#endif // DELAFDICT_H
