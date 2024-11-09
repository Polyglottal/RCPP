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

void parser(const std::string& text, std::vector<std::string>& wordlist)
{
    std::string word { "" };
    for (char c : text)
    {
        if (c != '.')
        {
            word += c;
        }

        if (c == ' ')
        {
            wordlist.push_back(word);
            word = "";
        }
    }

    for (int index {0}; index < static_cast<int>(wordlist.size()); index++)
    {
        std::cout << wordlist[index];
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
    parser(text, wordlist);
    collocationBuilder(wordlist, collList, 2);
    collocationBuilder(wordlist, threeBundleList, 3);
    collocationBuilder(wordlist, fourBundleList, 4);
}