#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
    private:
        std::string target;
    public:
        RobotomyRequestForm();
        RobotomyRequestForm(std::string& newTarget);
        RobotomyRequestForm(const RobotomyRequestForm& Other);
        RobotomyRequestForm&  operator=(const RobotomyRequestForm& Other);
        ~RobotomyRequestForm();
    
        void execute(Bureaucrat const & executor) const;
};

