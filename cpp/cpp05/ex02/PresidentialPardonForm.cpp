#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : target("default")
{
}

PresidentialPardonForm::PresidentialPardonForm(std::string& newTarget) : target(newTarget)
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& Other)
{
    this->target = Other.target;
}


PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& Other)
{
    this->target = Other.target;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
    if (PresidentialPardonForm::getGradeToSign() == 25
        && getGradeToExecute() == 5)
        std::cout << this->target << " has beeb pardoned by Zaphod Beeblebrox\n";

}