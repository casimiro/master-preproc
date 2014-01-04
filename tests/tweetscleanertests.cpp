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

TEST(TweetsCleanerTests, ChooseWordsShouldReturnCanonicalFormOfTheWords)
{
    DelafDict dict;
    dict.loadFromFile("fixtures/tweetsCleanerDelaf.dict");
    TweetsCleaner cleaner(dict);
    
    auto words = StringVector{"coisinhas", "basta"};
    auto expectedWords = StringVector{"coisa", "basto"};

    auto choosenWords = cleaner.chooseWords(words);
    
    ASSERT_EQ(expectedWords, choosenWords);
}

TEST(TweetsCleanerTests, ChooseWordsDiscardsWordsInForeignDicts)
{
    auto englishDict = StringUnorderedSet{std::string("you"), std::string("home"), std::string("fato")};
    auto spanishDict = StringUnorderedSet{std::string("madre"), std::string("nino"), std::string("sentido")};
    
    auto foreignDicts = StringUnorderedSets{englishDict, spanishDict};
    
    DelafDict dict;
    dict.loadFromFile("fixtures/tweetsCleanerDelaf.dict");
    TweetsCleaner cleaner(dict, foreignDicts);
    
    auto words = StringVector{std::string("you"), std::string("home"), std::string("fato"), std::string("madre"), std::string("nino"), std::string("sentido"), std::string("wireless")};
    auto expectedWords = StringVector{std::string("fato"), std::string("sentido"), std::string("wireless")};
    
    auto choosenWords = cleaner.chooseWords(words);
    
    ASSERT_EQ(expectedWords, choosenWords);
}

TEST(TweetsCleanerTests, ChooseWordsReturnsUnknownWords)
{
    DelafDict dict;
    dict.loadFromFile("fixtures/tweetsCleanerDelaf.dict");
    TweetsCleaner cleaner(dict);
    
    auto words = StringVector{std::string("asdfasdf"), std::string("dilma"), std::string("lula")};
    auto choosenWords = cleaner.chooseWords(words);
    
    ASSERT_EQ(words, choosenWords);
}

