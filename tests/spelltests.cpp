#include <gmock/gmock.h>
#include <vector>
#include "../spellchecker.h"

using namespace ::testing;
using namespace casimiro;

class SpellTests : public Test {
protected:
    virtual void SetUp()
    {
        spellChecker.prepare();
    }
    SpellChecker spellChecker;
};

TEST_F(SpellTests, GetSuggestedWords)
{
    StringVector words{std::string("csa"), std::string("futbol"), std::string("poltica"), std::string("asdfasdf")};
    StringVector expectedSuggestions{std::string("casa"), std::string("futebol"), std::string("politica")};
    
    auto suggestions = spellChecker.getSuggestions(words);
    
    ASSERT_EQ(expectedSuggestions, suggestions);
}

TEST_F(SpellTests, GetSuggestedWord)
{
    std::string word("csa");
    std::string expectedSuggestion("casa");
    
    auto suggestion = spellChecker.getSuggestion(word);
    
    ASSERT_EQ(expectedSuggestion, suggestion);
}

TEST_F(SpellTests, GetSuggestionForCorrectWord)
{
    auto word = std::string("lula");
    auto suggestion = spellChecker.getSuggestion(word);
    
    ASSERT_EQ(word, suggestion);
}

TEST_F(SpellTests, GetSuggestionIsLowerCase)
{
    auto word = std::string("dilma");
    auto suggestion = spellChecker.getSuggestion(word);
    
    ASSERT_EQ(word, suggestion);
}