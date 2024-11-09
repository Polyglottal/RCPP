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
        std::cout << wordlist[index] << ' ';
    }
    
}

int main ()
{
    std::string text { "Hello, how are you today. How am I today?" };
    std::vector<std::string> wordlist { }; // initialize an empty word list
    wordlist.reserve(20000); // reserve memory for 20000 words in the vector
    parser(text, wordlist);
}