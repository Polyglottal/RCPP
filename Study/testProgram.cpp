#include <string>
#include <iostream>

void parser(std::string& text)
{
    std::string word { "" };
    for (char& c : text)
    {
        if (c != '.')
        {
            word += c;
        }

        if (c == ' ')
        {
            std::cout << word << std::endl;
            word = "";
        }
    }
    
}

int main ()
{
    std::string text { "Hello, how are you today. How am I today?" };
    parser(text);
}