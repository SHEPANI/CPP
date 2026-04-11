#include "Bureaucrat.hpp"
class Bureaucrat;

class Form
{
    private:

        const std::string name;
        bool sign;
        int const signGrade; 
        int const exeGrade;

    public:

        Form();
        Form(const Form& Other);
        Form(const std::string& newName, int newSignG, int newExeG);
        Form& operator=(const Form& Other);
        ~Form();

        const std::string& getName() const;
        bool getSign() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;
        void beSigned(Bureaucrat& bureaucrat);

        class GradeTooHighException : public std::exception
        {
            public : // way 
                virtual const char* what() const throw()
                {   
                    return ("Error: Grade cannot be higher\n");
                }
        };

        class GradeTooLowException : public std::exception
        {
            private :  // way
                virtual const char* what() const throw()
                {
                    return ("Error: Grade cannot be lower\n");
                }
        };

};

std::ostream& operator<<(std::ostream& os,const Form& Other);
