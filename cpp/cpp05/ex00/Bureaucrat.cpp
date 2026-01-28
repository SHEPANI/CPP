/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:41:18 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/27 15:39:25 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
}

Bureaucrat::Bureaucrat(unsigned int newGrade)
{
    if (newGrade > 150 || newGrade < 1)
        throw -1;
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
    grade -= inc_grade;
}

void Bureaucrat::dec_burGrade(int dec_grade)
{
    grade -= dec_grade;
}
