/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:41:18 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/30 10:21:56 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
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
    this->grade += inc_grade;
    if (this->grade > 150)
    {
        this->grade -= inc_grade;
        throw GradeTooLowException();
    }
}

void Bureaucrat::dec_burGrade(int dec_grade)
{
    this->grade -= dec_grade;
    if (this->grade < 1)
    {
        this->grade += dec_grade;
        throw GradeTooHighException();
    }
}

std::ostream& operator<<(std::ostream& os,const Bureaucrat& Other)
{
    os << Other.getName() << ", bureaucrat grade " << Other.getGrade(); 
    return os;
}