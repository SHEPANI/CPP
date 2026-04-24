#include "ScalarConverter.hpp"


int main(int ac, char **av)
{
    if (!av[1] || !av[1][0])
        return 0;
    std::string str;
    ScalarConverter::convert(str.assign(av[1]));
}