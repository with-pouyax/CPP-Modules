#include <iostream>
#include <string>

std::string trimm (std::string str)
{
    int start = 0;
    int end = str.size() - 1;

    for (start; isspace(str[start]); start++);   
    for (end; isspace(str[end]); end--);
    return (str.substr(start, end));
}

std::string process (std::string argument)
{
    std::string trimmed = trimm(argument);
    std::cout << trimmed << "\n";

    return NULL;
}


int main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            process(argv[i]);
        }
    }
}