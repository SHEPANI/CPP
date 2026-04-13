#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm
{
    private:
        std::string target;
    public:
        RobotomyRequestForm();
        RobotomyRequestForm(const std::string& newTarget);
        RobotomyRequestForm(const RobotomyRequestForm& Other);
        RobotomyRequestForm&  operator=(const RobotomyRequestForm& Other);
        ~RobotomyRequestForm();
    
        void execute(Bureaucrat const & executor) const;
};

#endif