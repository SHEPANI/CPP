#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class Form 
{
    private:

        const std::string name;
        bool sign;
        const int signGrade; 
        const int exeGrade;

    public:

        Form();
        Form(const Form& Other);
        Form(const std::string& newName, int newSignGrade, int newExeGrade);
        Form& operator=(const Form& Other);
        ~Form();

        const std::string& getName() const;
        bool getSign() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;
        void beSigned(Bureaucrat& bureaucrat);

        class GradeTooHighException : public std::exception
        {
            public : 
                const char* what() const throw()
                {   
                    return ("Error: Grade cannot be higher\n");
                }
        };

        class GradeTooLowException : public std::exception
        {
            public : 
                const char* what() const throw()
                {
                    return ("Error: Grade cannot be lower\n");
                }
        };

};

std::ostream& operator<<(std::ostream& os,const Form& Other);
