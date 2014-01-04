#include <gmock/gmock.h>
#include <vector>
#include "../spellchecker.h"

using namespace casimiro;

TEST(SpellTests, GetSuggestedWords)
{
    SpellChecker spellChecker;
    spellChecker.prepare();
    StringVector words{std::string("csa"), std::string("futbol"), std::string("poltica"), std::string("asdfasdf")};
    StringVector expectedSuggestions{std::string("casa"), std::string("futebol"), std::string("politica")};
    
    auto suggestions = spellChecker.getSuggestions(words);
    
    ASSERT_EQ(expectedSuggestions, suggestions);
    
}

TEST(SpellTests, GetSuggestedWord)
{
    SpellChecker spellChecker;
    spellChecker.prepare();
    
    std::string word("csa");
    std::string expectedSuggestion("casa");
    
    auto suggestion = spellChecker.getSuggestion(word);
    
    ASSERT_EQ(expectedSuggestion, suggestion);
}

TEST(SpellTests, GetSuggestionForCorrectWord)
{
    SpellChecker spellChecker;
    spellChecker.prepare();
    
    auto word = std::string("lula");
    auto suggestion = spellChecker.getSuggestion(word);
    
    ASSERT_EQ(word, suggestion);
}

TEST(SpellTests, GetSuggestionIsLowerCase)
{
    SpellChecker spellChecker;
    spellChecker.prepare();
    
    auto word = std::string("dilma");
    auto suggestion = spellChecker.getSuggestion(word);
    
    ASSERT_EQ(word, suggestion);
}