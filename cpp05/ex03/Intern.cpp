/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:14:30 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 22:56:10 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern(){}
Intern::Intern(const Intern& Other)
{
    *this = Other;
}
Intern& Intern::operator=(const Intern& Other)
{
    (void)Other;
    return (*this);
}
Intern::~Intern(){}

AForm* Intern::ShrubberyCreation(const std::string& name, const std::string& target)
{
    (void)name;
    std::cout << "Intern creates " << "ShrubberyCreationForm" << "\n";
    return(new ShrubberyCreationForm(target));
}
AForm* Intern::RobotomyRequest(const std::string& name, const std::string& target)
{
    (void)name;
    std::cout << "Intern creates " << "RobotomyRequestForm" << "\n";
    return(new RobotomyRequestForm(target));
}
AForm* Intern::PresidentialPardon(const std::string& name, const std::string& target)
{
    (void)name;
    std::cout << "Intern creates " << "PresidentialPardonForm" << "\n";
    return(new PresidentialPardonForm(target));
}

AForm *Intern::makeForm(const std::string& name, const std::string& target)
{
    AForm* (Intern::*ptrToMemberFunc[])(const std::string& name, const std::string& target) = {
        &Intern::ShrubberyCreation,
        &Intern::RobotomyRequest,
        &Intern::PresidentialPardon
    };

    std::string Forms[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    int i = 0;
    while (i < 3 && name != Forms[i]) {
        i++;
    }

    if (i < 3) {
        return ((this->*ptrToMemberFunc[i])(name, target));
    }
    else
        std::cout << "Error : Form not found\n";
    return (NULL);
}

