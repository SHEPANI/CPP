#include "Bureaucrat.hpp"

class AForm
{
    private:

        const std::string name;
        bool sign;
        int const signGrade; 
        int const exeGrade;

    public:

        AForm();
        AForm(const AForm& Other);
        AForm(const std::string& newName, int newSignG, int newExeG);
        AForm& operator=(const AForm& Other);
        ~AForm();

        const std::string& getName() const;
        bool getSign() const;
        const int getGradeToSign() const;
        const int getGradeToExecute() const;
        void beSigned(Bureaucrat& bureaucrat);
        virtual void execute(Bureaucrat const & executor) const = 0;

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

std::ostream& operator<<(std::ostream& os,const AForm& Other);
