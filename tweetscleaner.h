#ifndef TWEETSCLEANER_H
#define TWEETSCLEANER_H

#include <string>
#include "delafdict.h"

namespace casimiro {

class TweetsCleaner
{
public:
    TweetsCleaner(const DelafDict& _delafDict);
    virtual ~TweetsCleaner();
    
    virtual void cleanTweets(const std::string& _inFile, const std::string& _outFile) const;
    
private:
    const DelafDict& m_delafDict;
};

}
#endif // TWEETSCLEANER_H
