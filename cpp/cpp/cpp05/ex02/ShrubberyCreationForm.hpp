#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
    private:
        std::string target;
    public:
        ShrubberyCreationForm();
        ShrubberyCreationForm(std::string& newTarget);
        ShrubberyCreationForm(const ShrubberyCreationForm& Other);
        ShrubberyCreationForm&  operator=(const ShrubberyCreationForm& Other);
        ~ShrubberyCreationForm();
    
        void execute(Bureaucrat const & executor) const;
};
