/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:41:18 by lhchiban          #+#    #+#             */
/*   Updated: 2026/03/11 21:58:49 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Default"), grade(150)
{
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

void Bureaucrat::inc_burGrade(int inc_grade)
{
    if ((this->grade -= inc_grade) < 1)
    {
        this->grade += inc_grade;
        throw GradeTooHighException();
    }
}

void Bureaucrat::dec_burGrade(int dec_grade)
{
    
    if ((this->grade += dec_grade) > 150)
    {
        this->grade -= dec_grade;
        throw GradeTooLowException();
    }
}

void Bureaucrat::signForm(Form& form)
{
    try
    {
        form.beSigned(*this);    
    }
    catch (std::exception& e)
    {
        std::cout << this->getName() << " couldn’t sign " << form.getName() << " because " << e.what() << "\n";
    }
    std::cout << this->getName() << " signed " << form.getName() << "\n";
}

std::ostream& operator<<(std::ostream& os,const Bureaucrat& Other)
{
    os << Other.getName() << ", bureaucrat grade " << Other.getGrade(); 
    return os;
}

