#include <string>
#include <vector>
#include <iostream>

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

    int collCounter { 0 };
    int threeBundleCounter { 0 };
    int fourBundleCounter { 0 };

    for (char c : text)
    {   
        if (c != '.')
        {
            word += c;
            coll += c;
            threeBundle += c;
            fourBundle += c;
        }

        if (c == ' ')
        {
            collCounter++;
            threeBundleCounter++;
            fourBundleCounter++;

            wordlist.push_back(word);
            word = {};

            if (collCounter == 2)
            { 
                collList.push_back(coll);
                coll = {};
                collCounter = 0;
            }

            if (threeBundleCounter == 3)
            {
                threeBundleList.push_back(threeBundle);
                threeBundle = {};
                threeBundleCounter = 0;
            }

            if (fourBundleCounter == 4)
            {
                fourBundleList.push_back(fourBundle);
                fourBundle = {};
                fourBundleCounter = 0;
            }
        }
    }

    std::cout << "Word list:" << std::endl;
    for (int index {0}; index < static_cast<int>(wordlist.size()); index++)
    {
        std::cout << wordlist[index] << std::endl;
    }
    std::cout << "Collocation list" << std::endl;
    for (int index {0}; index < static_cast<int>(collList.size()); index++)
    {
        std::cout << collList[index] << std::endl;
    }

    std::cout << "Lexical 3 bundles:" << std::endl;
    for (int index {0}; index < static_cast<int>(threeBundleList.size()); index++)
    {
        std::cout << threeBundleList[index] << std::endl;
    }

    std::cout << "Lexical four bundles:" << std::endl;
    for (int index {0}; index < static_cast<int>(fourBundleList.size()); index++)
    {
        std::cout << fourBundleList[index] << std::endl;
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

int main ()
{
    std::string text { "Hello, how are you today. How am I today?" };
    std::vector<std::string> wordlist { }; // initialize an empty word list
    std::vector<std::string> collList { };
    std::vector<std::string> threeBundleList { };
    std::vector<std::string> fourBundleList { };
    parser(text, wordlist, collList, threeBundleList, fourBundleList);
    //collocationBuilder(wordlist, collList, 2);
    //collocationBuilder(wordlist, threeBundleList, 3);
    //collocationBuilder(wordlist, fourBundleList, 4);
}