#ifndef DELAFDICT_H
#define DELAFDICT_H

#include <string>
#include <map>

namespace casimiro {

class DelafDict
{
public:
    DelafDict();

    virtual void loadFromFile(const std::string& _fileName);

    virtual bool hasWord(const std::string& _word) const;
    
    virtual std::string getCanonical(const std::string& _word) const;

private:
    std::map<std::string, std::string> m_words;
};

}


#endif // DELAFDICT_H
