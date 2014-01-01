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