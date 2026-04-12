/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:14:26 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 22:57:09 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"

class Intern
{
    private:
        AForm* ShrubberyCreation(const std::string& name, const std::string& target);
        AForm* RobotomyRequest(const std::string& name, const std::string& target);
        AForm* PresidentialPardon(const std::string& name, const std::string& target);     
    public:
        Intern();
        Intern(const Intern& Other);
        Intern& operator=(const Intern& Other);
        ~Intern();

        AForm *makeForm(const std::string& name, const std::string& target);
};

#endif