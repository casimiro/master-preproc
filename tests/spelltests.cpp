#include <gmock/gmock.h>
#include <vector>
#include "../spellchecker.h"

using namespace casimiro;

TEST(SpellTests, GetSuggestedWords)
{
    SpellChecker spellChecker;
    StringVector words{std::string("csa"), std::string("futbol"), std::string("poltica"), std::string("asdfasdf")};
    StringVector expectedSuggestions{std::string("casa"), std::string("futebol"), std::string("politica")};
    
    auto suggestions = spellChecker.getSuggestions(words);
    
    ASSERT_EQ(expectedSuggestions, suggestions);
    
}