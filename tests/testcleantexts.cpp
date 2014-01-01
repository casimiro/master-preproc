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

TEST(TestCleanTexts, TestRemoveMentions)
{
    std::string dirtyString;
    std::string cleanString;
    LoadStrings("fixtures/removeMentions.txt", dirtyString, cleanString);

    std::string cleaned = RemoveMentions(dirtyString);

    ASSERT_EQ(cleanString, cleaned);
}

TEST(TestCleanTexts, TestRemoveStopWords)
{
    std::string dirtyString;
    std::string cleanString;
    LoadStrings("fixtures/removeStopWords.txt", dirtyString, cleanString);

    std::string cleaned = RemoveStopWords(dirtyString);

    ASSERT_EQ(cleanString, cleaned);
}

TEST(TestGetWords, TestGetWordsFromText)
{
    std::string input;
    std::string output;
    LoadStrings("fixtures/getWordsFromText.txt", input, output);

    std::istringstream iss(output);
    std::vector<std::string> expectedWords{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

    auto words = GetWordsFromText(input);

    ASSERT_EQ(expectedWords, words);
}


