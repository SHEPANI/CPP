#include <iostream>
#include <string>
#include <exception>
#include <iomanip>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& Other);
        ScalarConverter& operator=(const ScalarConverter& other);
        ~ScalarConverter();
    public:
        static void convert(std::string& str);
};