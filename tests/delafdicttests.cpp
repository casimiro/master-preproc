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
