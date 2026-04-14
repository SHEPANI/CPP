


#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("defaultShrubberyCreationForm", 145, 137)
{
    target = "default";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& newTarget) : AForm("defaultShrubberyCreationForm", 145, 137)
{
    this->target = newTarget;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& Other) :  AForm(Other.getName(), Other.getGradeToSign(), Other.getGradeToExecute())
{
    this->target = Other.target;
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