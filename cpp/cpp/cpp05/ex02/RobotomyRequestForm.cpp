#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : target("default")
{
}

RobotomyRequestForm::RobotomyRequestForm(std::string& newTarget) : target(newTarget)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& Other)
{
    this->target = Other.target;
}


RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& Other)
{
    this->target = Other.target;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
    if (RobotomyRequestForm::getGradeToSign() == 72
        && getGradeToExecute() == 45)
        std::cout << this->target << " has beeb pardoned by Zaphod Beeblebrox\n";

}