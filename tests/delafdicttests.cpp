#include <gmock/gmock.h>
#include "../delafdict.h"

using namespace casimiro;

TEST(DelafDictTests, DictLoadedFromFileHasWordsWithoutAccents)
{
    DelafDict delafDict;
    delafDict.loadFromFile("fixtures/delaf.dict");

    ASSERT_TRUE(delafDict.hasWord("abaetetubenses"));
    ASSERT_TRUE(delafDict.hasWord("abaetetubense"));
    ASSERT_TRUE(delafDict.hasWord("abafadicas"));
    ASSERT_TRUE(delafDict.hasWord("abafadica"));

    ASSERT_FALSE(delafDict.hasWord("inexistente"));
}

TEST(DelafDictTests, DictLoadedFromFileHasWordsInLowerCase)
{
    DelafDict delafDict;
    delafDict.loadFromFile("fixtures/delaf.dict");
    
    ASSERT_TRUE(delafDict.hasWord("usp"));
    ASSERT_FALSE(delafDict.hasWord("USP"));
}

TEST(DelafDictTests, DictLoadedFromFileHasCorrectCanonicalWords)
{
    DelafDict delafDict;
    delafDict.loadFromFile("fixtures/delaf.dict");
    
    ASSERT_EQ(std::string("abaetetubense"), delafDict.getCanonical("abaetetubenses"));
    ASSERT_EQ(std::string("abafadico"), delafDict.getCanonical("abafadicas"));
    ASSERT_EQ(std::string("abaetetubense"), delafDict.getCanonical("abaetetubense"));
}

TEST(DelafDictTests, DictLoadedFromFileHasCorrectWordTypes)
{
    DelafDict delafDict;
    delafDict.loadFromFile("fixtures/delaf.dict");
    
    ASSERT_EQ(Adjective, delafDict.getWordType("abaetetubenses"));
    ASSERT_EQ(Noun, delafDict.getWordType("carro"));
    ASSERT_EQ(Abbreviation, delafDict.getWordType("ml"));
    ASSERT_EQ(Acronym, delafDict.getWordType("usp"));
    ASSERT_EQ(UnknownWordType, delafDict.getWordType("pos"));
}
