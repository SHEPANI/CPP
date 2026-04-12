

#include "Bureaucrat.hpp"

AForm::AForm() : name("defaultForm"), signGrade(150), exeGrade(150)
{
    sign = false;
}

AForm::AForm(const std::string& newName, int newSignG, int newExeG) : name(newName),
            signGrade(newSignG), exeGrade(newExeG)
{
    if (newSignG > 150 || newExeG > 150)
        throw GradeTooLowException();
    if (newSignG < 1 || newExeG < 1)
        throw GradeTooHighException();
}

AForm::AForm(const AForm& Other) : name(Other.name), signGrade(Other.signGrade)
                    , exeGrade(Other.exeGrade)
{
    this->sign = Other.sign;
}

AForm& AForm::operator=(const AForm& Other) 
{
    this->sign = Other.sign;
    return (*this);
}

AForm::~AForm()
{
}

bool AForm::getSign() const
{
    return(this->sign);
}

const std::string& AForm::getName() const
{
    return (this->name);
}

int AForm::getGradeToSign() const
{
   return (this->signGrade); 
}

int AForm::getGradeToExecute() const
{
    return (this->exeGrade);
}

void AForm::beSigned(Bureaucrat& bureaucrat)
{
    if (bureaucrat.getGrade() > this->getGradeToSign())
    {
        throw GradeTooLowException();
    }
    this->sign = true;
}


std::ostream& operator<<(std::ostream& os, const AForm& Other)
{
    os << "AForm name is " << Other.getName() << "\n AForm sign : " << Other.getSign() 
    << "\nForm sign grade : " << Other.getGradeToSign() 
    << "\nForm execute grade : " << Other.getGradeToSign() << "\n";
    return os;
}

