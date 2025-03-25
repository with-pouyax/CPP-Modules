#include <iostream>
#include <string>

std::string upper(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
        str[i] = toupper(str[i]);
    return str;
}

void process(std::string argument)
{
    if (argument.empty()) return;
    std::cout << upper(argument);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            process(argv[i]);
        }
    }
    std::cout << std::endl;
    return 0;
}