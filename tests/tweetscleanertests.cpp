#include <gmock/gmock.h>
#include <fstream>
#include "../tweetscleaner.h"
#include "../delafdict.h"

using namespace casimiro;

TEST(TweetsCleanerTests, OutputHasOnlyCanonicals)
{
    DelafDict dict;
    dict.loadFromFile("fixtures/tweetsCleanerDelaf.dict");
    
    TweetsCleaner cleaner(dict);
    cleaner.cleanTweets("fixtures/tweetsCleanerOutputCanonicalIn.txt", "fixtures/tweetsCleanerOutputCanonicalOut.txt");

    std::ifstream outFile("fixtures/tweetsCleanerOutputCanonicalOut.txt");
    std::string outContent( (std::istreambuf_iterator<char>(outFile) ), (std::istreambuf_iterator<char>()));
    
    std::ifstream expectedFile("fixtures/tweetsCleanerOutputCanonicalExpected.txt");
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), (std::istreambuf_iterator<char>()));
    
    ASSERT_EQ(expectedContent, outContent);
}
