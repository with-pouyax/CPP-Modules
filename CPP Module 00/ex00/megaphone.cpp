// Hedge case: ./megaphone "$(printf 'Hello\xFFWorld')"

#include <iostream>
#include <string>

std::string trimm(std::string str)
{
    int start;
    int end;

    for (start = 0; isspace(str[start]); start++);
    for (end = str.size() - 1; isspace(str[end]); end--);
    if (start > end) return "";

    return str.substr(start, (end - start ) + 1);
}

std::string upper(std::string str)
{
    for (int i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
    return str;
}

void process (std::string argument, int i)
{
    if (argument.empty()) return;
    argument = trimm(argument);
    argument = upper(argument);
    
    //std::cout << "+" <<argument << "+";
    if (argument.empty()) return;
    std::cout << (i == 1 ? argument : " " + argument);
    return;
}


int main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            process(argv[i], i);
        }
    }
    std::cout<< ".\n";
}