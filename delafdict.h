#ifndef DELAFDICT_H
#define DELAFDICT_H

#include <string>
#include <set>

namespace casimiro {

class DelafDict
{
public:
    DelafDict();

    virtual void loadFromFile(const std::string& _fileName);

    virtual bool hasWord(const std::string& _word);

private:
    std::set<std::string> m_words;
};

}


#endif // DELAFDICT_H
