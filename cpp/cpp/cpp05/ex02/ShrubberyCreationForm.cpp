


#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("default", 145, 137)
{
    target = "default";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& newTarget) : AForm("default", 145, 137)
{
    this->target = newTarget;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& Other)
{
    *this = Other;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& Other)
{
    this->target = Other.target;
    return(*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    if (!this->getSign() || executor.getGrade() > this->getGradeToExecute())
    {
        if (!this->getSign())
            throw FormNotSignedExeption();
        throw GradeTooLowException();
    }
    std::ofstream outFile(this->target + "_shrubbery");
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