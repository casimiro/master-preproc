#include <gmock/gmock.h>
#include <fstream>
#include "../utils.h"

using namespace casimiro;

TEST(TestCleanTexts, TestReplaceNonAsciiChars)
{
    std::ifstream file("fixtures/removeNonAsciiData.txt");
    std::string dirtyString;
    std::string cleanString;
    
    std::getline(file, dirtyString);
    std::getline(file, cleanString);
    
    std::string cleanedString = ReplaceNonAsciiChars(dirtyString);
    
    ASSERT_EQ(cleanString, cleanedString);
}

TEST(TestCleanTexts, TestRemoveLaughs)
{
    std::ifstream file("fixtures/removeLaughData.txt");
    std::string dirtyString;
    std::string cleanString;
    
    std::getline(file, dirtyString);
    std::getline(file, cleanString);
    
    std::string cleaned = RemoveLaughs(dirtyString);
    ASSERT_EQ(cleanString, cleaned);
}

TEST(TestCleanTexts, TestRemoveURLs)
{
    std::ifstream file("fixtures/removeURLs.txt");
    std::string dirtyString;
    std::string cleanString;
    
    std::getline(file, dirtyString);
    std::getline(file, cleanString);
    
    std::string cleaned = RemoveURLs(dirtyString);
    ASSERT_EQ(cleanString, cleaned);
}
