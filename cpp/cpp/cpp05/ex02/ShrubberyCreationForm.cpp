


#include "ShrubberyCreationForm.hpp"
#include <fstream>

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    if (ShrubberyCreationForm::getGradeToSign() == 145
        && ShrubberyCreationForm::getGradeToExecute() == 137)
    {
        std::ofstream outFile(this->target + "_shrubbery");
        if (outFile.is_open())
            std::cout << "succes\n";
        else   
            std::cout << "not succes\n";
        
        outFile <<
            "       _-_\n"
            "    /~~   ~~\\\n"
            " /~~         ~~\\\n"
            "{               }\n"
            " \\  _-     -_  /\n"
            "   ~  \\\\ //  ~\n"
            "_- -   | | _- _\n"
            "  _ -  | |   -_\n"
            "      / / \\ \n";
        outFile.close();
    }

}