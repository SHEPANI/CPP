


#include "ShrubberyCreationForm.hpp"


void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    if (ShrubberyCreationForm::getGradeToSign() == 145
        && getGradeToExecute() == 137)
        std::cout << this->target << " has beeb pardoned by Zaphod Beeblebrox\n";

}