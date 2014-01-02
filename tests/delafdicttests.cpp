#include <gmock/gmock.h>
#include "../delafdict.h"

using namespace casimiro;
using namespace ::testing;

class DelafDictTests : public Test {
protected:
    
    virtual void SetUp()
    {
        delafDict.loadFromFile("fixtures/delaf.dict");
    }
    
    DelafDict delafDict;
};

TEST_F(DelafDictTests, DictLoadedFromFileHasWordsWithoutAccents)
{
    ASSERT_TRUE(delafDict.hasWord("abaetetubenses"));
    ASSERT_TRUE(delafDict.hasWord("abaetetubense"));
    ASSERT_TRUE(delafDict.hasWord("abafadicas"));
    ASSERT_TRUE(delafDict.hasWord("abafadica"));

    ASSERT_FALSE(delafDict.hasWord("inexistente"));
}

TEST_F(DelafDictTests, DictLoadedFromFileHasWordsInLowerCase)
{
    ASSERT_TRUE(delafDict.hasWord("usp"));
    ASSERT_FALSE(delafDict.hasWord("USP"));
}

TEST_F(DelafDictTests, DictLoadedFromFileHasCorrectCanonicalWords)
{
    ASSERT_EQ(std::string("abaetetubense"), delafDict.getCanonical("abaetetubenses"));
    ASSERT_EQ(std::string("abafadico"), delafDict.getCanonical("abafadicas"));
    ASSERT_EQ(std::string("abaetetubense"), delafDict.getCanonical("abaetetubense"));
}

TEST_F(DelafDictTests, DictLoadedFromFileHasCorrectWordTypes)
{
    ASSERT_EQ(Adjective, delafDict.getWordType("abaetetubenses"));
    ASSERT_EQ(Noun, delafDict.getWordType("carro"));
    ASSERT_EQ(Abbreviation, delafDict.getWordType("ml"));
    ASSERT_EQ(Acronym, delafDict.getWordType("usp"));
    ASSERT_EQ(UnknownWordType, delafDict.getWordType("pos"));
}

TEST_F(DelafDictTests, ExtractUnknownWords)
{
    auto words = StringVector{
        std::string("abaetetubense"), std::string("abaetetubenses"), 
        std::string("artificial"), std::string("piano")
    };
    auto expectedUnkwonWords = StringVector{std::string("artificial"), std::string("piano")};
    
    auto unknownWords = delafDict.getUnknownWords(words);
    
    ASSERT_EQ(expectedUnkwonWords, unknownWords);
}

TEST_F(DelafDictTests, GetNouns)
{
    auto words = StringVector{
        std::string("abaetetubense"), std::string("abaetetubenses"), 
        std::string("artificial"), std::string("piano"),
        std::string("usp"), std::string("carro"), std::string("ml")
    };
    auto expectedNouns = StringVector{std::string("usp"), std::string("carro"), std::string("ml")};
    
    auto nouns = delafDict.getNouns(words);
    
    ASSERT_EQ(expectedNouns, nouns);
}
