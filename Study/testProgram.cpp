#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "punctuation.h"

// void parser(std::string& text)
// {
//     std::string word { "" };
//     for (char& c : text)
//     {
//         if (c != '.')
//         {
//             word += c;
//         }

//         if (c == ' ')
//         {
//             std::cout << word << std::endl;
//             word = "";
//         }
//     }
    
// }


// Using const invokes move semantics (no copy will be made)
// so in the for loop char c must not be char& c.
// Using const means we cannot modify the string passed by reference
// so the original text in main will not accidentally be modified
// Instead the copy is made by char c in the for loop, so remove the
// & pass-by-reference on char& c otherwise it conflicts with const.



// But imagine if we could build the collocation lists here! It could be done in one go!
void parser(
    const std::string& text, 
    std::vector<std::string>& wordlist, 
    std::vector<std::string>& collList,
    std::vector<std::string>& threeBundleList,
    std::vector<std::string>& fourBundleList
)
{
    std::string word { };
    std::string coll { };
    std::string threeBundle { };
    std::string fourBundle { };

    // Using an iterator lets me detect when I have reached the end of the string
    for (auto iterator = text.begin(); iterator != text.end(); ++iterator)
    {   
        const char c = *iterator;
        if (!Punctuation::isPunctuation(c))
        {
            word += c;
            coll += c;
            threeBundle += c;
            fourBundle += c;
        }

        if (c == ' ' || std::next(iterator) == text.end())
        {

            if (fourBundle != threeBundle)
            {
                fourBundleList.push_back(fourBundle);
                fourBundle = threeBundle;
            }

            if (threeBundle != coll)
            {
                threeBundleList.push_back(threeBundle);
                threeBundle = coll;
            }

            if (coll != word)
            {
                collList.push_back(coll);
                coll = word;
            }

            wordlist.push_back(word);
            word = {};

        }
    }
}

void collocationBuilder(const std::vector<std::string>& wordlist, std::vector<std::string>& collList, const int collSize)
{
    std::string coll { };
    for (int index {0}; index < static_cast<int>(wordlist.size() - (collSize - 1)); index++)
    {
        for (int j {index}; j <= index + collSize - 1; j++) {
            coll += wordlist[j];
        }
        // coll += wordlist[index] + wordlist[index + 1];
        collList.push_back(coll);
        coll = {};
    }
    for (int index {0}; index < static_cast<int>(collList.size()); index++)
    {
        std::cout << collList[index] << std::endl;
    }
}

void printListHeads(
    const std::vector<std::string>& wordlist,
    const std::vector<std::string>& collList,
    const std::vector<std::string>& threeBundleList,
    const std::vector<std::string>& fourBundleList,
    int headLength
)
{
    std::cout << "Word list:" << std::endl;
    for (int index {0}; index < headLength; index++)
    {
        std::cout << wordlist[index] << std::endl;
    }
    std::cout << "Collocation list" << std::endl;
    for (int index {0}; index < headLength; index++)
    {
        std::cout << collList[index] << std::endl;
    }

    std::cout << "Lexical 3 bundles:" << std::endl;
    for (int index {0}; index < headLength; index++)
    {
        std::cout << threeBundleList[index] << std::endl;
    }

    std::cout << "Lexical four bundles:" << std::endl;
    for (int index {0}; index < headLength; index++)
    {
        std::cout << fourBundleList[index] << std::endl;
    }
}

int main ()
{
    std::string text { "Hello, how are you today. How am I today?" };

    std::vector<std::string> wordlist { }; // initialize an empty word list
    std::vector<std::string> collList { };
    std::vector<std::string> threeBundleList { };
    std::vector<std::string> fourBundleList { };

    std::ifstream f("sample.txt");
    if (!f.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    std::string allContent;
    while (std::getline(f, line)) {
        allContent += line;
    }
    parser(allContent, wordlist, collList, threeBundleList, fourBundleList);

    printListHeads(wordlist, collList, threeBundleList, fourBundleList, 100);
    std::cout << wordlist.size() << " " << collList.size() << " " << threeBundleList.size() << " " << fourBundleList.size() << std::endl;

    
    //collocationBuilder(wordlist, collList, 2);
    //collocationBuilder(wordlist, threeBundleList, 3);
    //collocationBuilder(wordlist, fourBundleList, 4);
}