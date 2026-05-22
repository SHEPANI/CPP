#include "ScalarConverter.hpp"
#include <iostream>


int main(int ac, char **av)
{
    if (!av[1] || !av[1][0] || ac != 2)
        return (std::cout << "Usage: " << av[0] << " <input_literal>" << "\n", 1);
    ScalarConverter::convert(av[1]);
    return 0;
}