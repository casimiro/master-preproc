#include <gmock/gmock.h>
#include <fstream>
#include "../tweetscleaner.h"
#include "../delafdict.h"
#include "../spellchecker.h"

using namespace ::testing;
using namespace casimiro;

class TweetsCleanerTests : public Test {
protected:
    
    TweetsCleanerTests():
        cleaner(dict, foreignDicts, speller)
    {
    }
    
    virtual void SetUp()
    {
        dict.loadFromFile("fixtures/tweetsCleanerDelaf.dict");
        speller.prepare();
    }
    
    StringUnorderedSets foreignDicts;
    DelafDict dict;
    SpellChecker speller;
    TweetsCleaner cleaner;
};

TEST_F(TweetsCleanerTests, OutputHasOnlyCanonicals)
{
    bool spelling = false;
    cleaner.cleanTweets("fixtures/tweetsCleanerOutputCanonicalIn.txt", "fixtures/tweetsCleanerOutputCanonicalOut.txt", spelling);

    std::ifstream outFile("fixtures/tweetsCleanerOutputCanonicalOut.txt");
    std::string outContent( (std::istreambuf_iterator<char>(outFile) ), (std::istreambuf_iterator<char>()));
    
    std::ifstream expectedFile("fixtures/tweetsCleanerOutputCanonicalExpected.txt");
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), (std::istreambuf_iterator<char>()));
    
    ASSERT_EQ(expectedContent, outContent);
}

TEST_F(TweetsCleanerTests, ChooseWordsShouldReturnCanonicalFormOfTheWords)
{
    auto words = StringVector{"coisinhas", "basta"};
    auto expectedWords = StringVector{"coisa", "basto"};

    auto choosenWords = cleaner.chooseWords(words);
    
    ASSERT_EQ(expectedWords, choosenWords);
}

TEST_F(TweetsCleanerTests, ChooseWordsDiscardsWordsInForeignDicts)
{
    foreignDicts.push_back(StringUnorderedSet{std::string("you"), std::string("home"), std::string("fato")});
    foreignDicts.push_back(StringUnorderedSet{std::string("madre"), std::string("nino"), std::string("sentido")});
    
    auto words = StringVector{std::string("you"), std::string("home"), std::string("fato"), std::string("madre"), std::string("nino"), std::string("sentido"), std::string("wireless")};
    auto expectedWords = StringVector{std::string("fato"), std::string("sentido"), std::string("wireless")};
    
    auto choosenWords = cleaner.chooseWords(words);
    
    ASSERT_EQ(expectedWords, choosenWords);
}

TEST_F(TweetsCleanerTests, ChooseWordsReturnsUnknownWords)
{
    auto words = StringVector{std::string("asdfasdf"), std::string("dilma"), std::string("lula")};
    auto choosenWords = cleaner.chooseWords(words);
    
    ASSERT_EQ(words, choosenWords);
}


TEST_F(TweetsCleanerTests, ChooseWordsTryToCorrectUnknownWordsWhenItsAskedTo)
{
    auto words = StringVector{std::string("csa"), std::string("futbol"), std::string("poltica"), std::string("asdfasdf")};
    auto expectedWords = StringVector{std::string("casa"), std::string("futebol"), std::string("politica"), std::string("asdfasdf")};
    
    bool spelling = true;
    auto choosenWords = cleaner.chooseWords(words, spelling);
    
    ASSERT_EQ(expectedWords, choosenWords);
}

TEST_F(TweetsCleanerTests, ChooseWordsDoesNotTryToCorrectUnknownWords)
{
    auto words = StringVector{std::string("csa"), std::string("futbol"), std::string("poltica"), std::string("asdfasdf")};
    
    auto choosenWords = cleaner.chooseWords(words);
    
    ASSERT_EQ(words, choosenWords);
}

TEST_F(TweetsCleanerTests, cleanTweetsDiscardsTweetsWithLessChoosenWordsThanGivenAcceptable)
{
    bool spelling = true;
    int minChoosenWords = 5;
    
    cleaner.cleanTweets("fixtures/tweetsCleanerDiscardsTweetsWithFewChoosenWordsIn.txt", "fixtures/tweetsCleanerDiscardsTweetsWithFewChoosenWordsOut.txt", spelling, minChoosenWords);

    std::ifstream outFile("fixtures/tweetsCleanerDiscardsTweetsWithFewChoosenWordsOut.txt");
    std::string outContent( (std::istreambuf_iterator<char>(outFile) ), (std::istreambuf_iterator<char>()));
    
    std::ifstream expectedFile("fixtures/tweetsCleanerDiscardsTweetsWithFewChoosenWordsExpected.txt");
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), (std::istreambuf_iterator<char>()));
    
    ASSERT_EQ(expectedContent, outContent);
}

TEST_F(TweetsCleanerTests, cleanTweetsDiscardsTweetsWithUnknownWordRateAboveGivenAcceptable)
{
    bool spelling = true;
    int minChoosenWords = 0;
    double maxUnknownRate = 0.2;

    cleaner.cleanTweets("fixtures/tweetsCleanerDiscardsTweetsWithHighUnknownWordsRateIn.txt", "fixtures/tweetsCleanerDiscardsTweetsWithHighUnknownWordsRateOut.txt", spelling, minChoosenWords, maxUnknownRate);

    std::ifstream outFile("fixtures/tweetsCleanerDiscardsTweetsWithHighUnknownWordsRateOut.txt");
    std::string outContent( (std::istreambuf_iterator<char>(outFile) ), (std::istreambuf_iterator<char>()));
    
    std::ifstream expectedFile("fixtures/tweetsCleanerDiscardsTweetsWithHighUnknownWordsRateExpected.txt");
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), (std::istreambuf_iterator<char>()));
    
    ASSERT_EQ(expectedContent, outContent);
}