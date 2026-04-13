#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "Bureaucrat.hpp"

class ShrubberyCreationForm : public AForm
{
    private:
        std::string target;
    public:
        ShrubberyCreationForm();
        ShrubberyCreationForm(const std::string& newTarget);
        ShrubberyCreationForm(const ShrubberyCreationForm& Other);
        ShrubberyCreationForm&  operator=(const ShrubberyCreationForm& Other);
        ~ShrubberyCreationForm();
    
        void execute(Bureaucrat const & executor) const;
};

#endif