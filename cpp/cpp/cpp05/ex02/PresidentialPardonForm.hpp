#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
    private:
        std::string target;
    public:
        PresidentialPardonForm();
        PresidentialPardonForm(std::string& newTarget);
        PresidentialPardonForm(const PresidentialPardonForm& Other);
        PresidentialPardonForm&  operator=(const PresidentialPardonForm& Other);
        ~PresidentialPardonForm();
    
        void execute(Bureaucrat const & executor) const;
};

