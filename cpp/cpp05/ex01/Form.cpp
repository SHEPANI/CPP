

#include <Form.hpp>



Form::Form() : name("default"), signGrade(150), exeGrade(150)
{
    sign = false;
}

Form::Form(const std::string& newName, int newSignG, int newExeG) : name(newName),
            signGrade(newSignG), exeGrade(newExeG)
{
    if (newSignG > 150 || newExeG > 150)
        throw GradeTooLowException();
    if (newSignG < 1 || newExeG < 1)
        throw GradeTooHighException();
}

Form::Form(const Form& Other) : name(Other.name), signGrade(Other.signGrade)
                    , exeGrade(Other.exeGrade)
{
    this->sign = Other.sign;
}

Form& Form::operator=(const Form& Other) 
{
    *this = Other;
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

const int Form::getGradeToSign() const // check name of func of currect
{
   return (this->signGrade); 
}

const int Form::getGradeToExecute() const // check name of func of currect
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
    os << "Form name is " << Other.getName() << "\n Form sign : " << Other.getSign() 
    << "\nForm sign grade : " << Other.getGradeToSign() 
    << "\nForm execute grade : " << Other.getGradeToSign();
    return os;
}

