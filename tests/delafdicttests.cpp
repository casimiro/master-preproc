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
