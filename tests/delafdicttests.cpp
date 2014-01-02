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

TEST(DelafDictTests, DictLoadedFromFileHasCorrectCanonicalWords)
{
    DelafDict delafDict;
    delafDict.loadFromFile("fixtures/delaf.dict");
    
    ASSERT_EQ(std::string("abaetetubense"), delafDict.getCanonical("abaetetubenses"));
    ASSERT_EQ(std::string("abafadico"), delafDict.getCanonical("abafadicas"));
    ASSERT_EQ(std::string("abaetetubense"), delafDict.getCanonical("abaetetubense"));
}