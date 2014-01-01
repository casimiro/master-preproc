#include <gmock/gmock.h>
#include <fstream>
#include "../utils.h"

using namespace casimiro;

void LoadStrings(const std::string& _fileName, std::string& _dirty, std::string& _clean)
{
    std::ifstream file(_fileName);
    std::getline(file, _dirty);
    std::getline(file, _clean);
}

TEST(TestCleanTexts, TestReplaceNonAsciiChars)
{
    std::string dirtyString;
    std::string cleanString;
    LoadStrings("fixtures/removeNonAsciiData.txt", dirtyString, cleanString);
    
    std::string cleanedString = ReplaceNonAsciiChars(dirtyString);
    
    ASSERT_EQ(cleanString, cleanedString);
}

TEST(TestCleanTexts, TestRemoveLaughs)
{
    std::string dirtyString;
    std::string cleanString;
    LoadStrings("fixtures/removeLaughData.txt", dirtyString, cleanString);
    
    std::string cleaned = RemoveLaughs(dirtyString);
    
    ASSERT_EQ(cleanString, cleaned);
}

TEST(TestCleanTexts, TestRemoveURLs)
{
    std::string dirtyString;
    std::string cleanString;
    LoadStrings("fixtures/removeURLs.txt", dirtyString, cleanString);
    
    std::string cleaned = RemoveURLs(dirtyString);
    
    ASSERT_EQ(cleanString, cleaned);
}
