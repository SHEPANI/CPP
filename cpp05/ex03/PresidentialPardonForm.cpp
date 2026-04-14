#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() :  AForm("DefaultPresidentialPardonForm", 25, 5), target("default")
{
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& newTarget) : AForm("DefaultPresidentialPardonForm", 25, 5), target(newTarget) 
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& Other) :  AForm(Other)
{
    this->target = Other.target;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& Other)
{
    this->target = Other.target;
    return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
    if (!this->getSign() || executor.getGrade() > this->getGradeToExecute())
    {
        if (!this->getSign())
            throw FormNotSignedExeption();
        throw GradeTooLowException();
    }
    std::cout << this->target << " has been pardoned by Zaphod Beeblebrox\n";
}