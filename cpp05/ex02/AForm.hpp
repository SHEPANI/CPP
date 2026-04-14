#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm
{
    private:

        const std::string name;
        bool sign;
        const int signGrade; 
        const int exeGrade;

    public:

        AForm();
        AForm(const AForm& Other);
        AForm(const std::string& newName, int newSignGrade, int newExeGrade);
        AForm& operator=(const AForm& Other);
        virtual ~AForm();

        const std::string& getName() const;
        bool getSign() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;
        void beSigned(Bureaucrat& bureaucrat);
        virtual void execute(Bureaucrat const & executor) const = 0;

        class GradeTooHighException : public std::exception
        {
            public : 
                const char* what() const throw();
        };

        class GradeTooLowException : public std::exception
        {
            public :
                const char* what() const throw();
        };

        class FormNotSignedExeption : public std::exception
        {
            public :
                const char* what() const throw();
        };

};

std::ostream& operator<<(std::ostream& os,const AForm& Other);

#endif