#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
{
    this->target = "default";
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& newTarget) : AForm("DefaultRobotomyRequestForm", 72, 4)
{
    this->target = newTarget;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& Other)
{
    this->target = Other.target;
}


RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& Other)
{
    this->target = Other.target;
    return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
    if (!this->getSign() || executor.getGrade() > this->getGradeToExecute())
    {
        if (!this->getSign())
            throw FormNotSignedExeption();
        throw GradeTooLowException();
    }
    std::cout << "BZZZZZTT! DRILL DRILL DRILL...\n";
    static int flag;
    if (!flag)
    {
        srand(time(NULL));
        flag = 1;
    }
    if (rand() % 2)
        std::cout << this->target << " has been robotomized\n";
    else
        std::cout << "the robotomy failed\n";
}