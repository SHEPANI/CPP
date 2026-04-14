/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:41:18 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 15:56:35 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("DefaultBureaucrat")
{
    grade = 150;
}

Bureaucrat::Bureaucrat(int newGrade, const std::string& newName) : name(newName)
{
    if (newGrade > 150)
        throw GradeTooLowException();
    if (newGrade < 1)
        throw GradeTooHighException();
    this->grade = newGrade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& Other) : name(Other.name)
{
    this->grade = Other.grade;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& Other)
{
    this->grade = Other.grade;
    return (*this);
}

Bureaucrat::~Bureaucrat()
{
}

const std::string& Bureaucrat::getName() const
{
    return (this->name);
}

int Bureaucrat::getGrade() const
{
   return (this->grade); 
}

void Bureaucrat::inc_burGrade()
{
    if ((this->grade -= 1) < 1)
    {
        this->grade += 1;
        throw GradeTooHighException();
    }
}

void Bureaucrat::dec_burGrade()
{
    
    if ((this->grade += 1) > 150)
    {
        this->grade -= 1;
        throw GradeTooLowException();
    }
}

void Bureaucrat::signForm(Form& form)
{
    try
    {
        form.beSigned(*this);
        std::cout << this->getName() << " signed " << form.getName() << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << this->getName() << " couldn't sign " << form.getName() << " because " << e.what();
    }
}

const char* Bureaucrat::GradeTooLowException::what() const throw(){return ("Error: Grade is to lower\n");}
const char* Bureaucrat::GradeTooHighException::what() const throw(){return ("Error: Grade is to higher\n");}

std::ostream& operator<<(std::ostream& os,const Bureaucrat& Other)
{
    os << Other.getName() << ", bureaucrat grade " << Other.getGrade() << ".\n"; 
    return os;
}

