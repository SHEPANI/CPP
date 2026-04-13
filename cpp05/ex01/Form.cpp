#include "Bureaucrat.hpp"

Form::Form() : name("defaultForm"), signGrade(150), exeGrade(150)
{
    sign = false;
}

Form::Form(const std::string& newName, int newSignGrade, int newExeGrade) : name(newName),
            sign(false), signGrade(newSignGrade), exeGrade(newExeGrade)
{
    if (newSignGrade > 150 || newExeGrade > 150)
        throw GradeTooLowException();
    if (newSignGrade < 1 || newExeGrade < 1)
        throw GradeTooHighException();
}

Form::Form(const Form& Other) : name(Other.name), signGrade(Other.signGrade)
                    , exeGrade(Other.exeGrade)
{
    this->sign = Other.sign;
}

Form& Form::operator=(const Form& Other) 
{
    this->sign = Other.sign;
    return (*this);
}

Form::~Form()
{
}

bool Form::getSign() const
{
    return(this->sign);
}

const std::string& Form::getName() const
{
    return (this->name);
}

int Form::getGradeToSign() const 
{
   return (this->signGrade); 
}

int Form::getGradeToExecute() const
{
    return (this->exeGrade);
}

void Form::beSigned(Bureaucrat& bureaucrat)
{
    if (bureaucrat.getGrade() > this->getGradeToSign())
    {
        throw GradeTooLowException();
    }
    this->sign = true;
}


std::ostream& operator<<(std::ostream& os, const Form& Other)
{
    os << "Form name is " << Other.getName() << "\nForm sign : " << Other.getSign() 
    << "\nForm sign grade : " << Other.getGradeToSign() 
    << "\nForm execute grade : " << Other.getGradeToExecute() << "\n";
    return os;
}

