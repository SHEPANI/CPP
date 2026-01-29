/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:26:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/29 12:58:16 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream> // why string is builting her
#include <string>
#include <ostream>
#include <exception>

class Bureaucrat
{
    protected:
        const std::string name;
        int   grade;
    public:
        Bureaucrat();
        Bureaucrat(int newGrade, const std::string& newName);
        Bureaucrat(const Bureaucrat& Other);
        Bureaucrat& operator=(const Bureaucrat& Other);
        ~Bureaucrat();

        const std::string& getName() const;
        int getGrade() const;
        void inc_burGrade(int inc_grade);
        void dec_burGrade(int dec_grade);
        class GradeTooHighException : public std::exception
        {
            public : // way 
                virtual const char* what() const throw()
                {
                    return ("Error: Grade cannot be higher\n");
                }
        };
        class GradeTooLowException : public std::exception
        {
            private :  // way
                virtual const char* what() const throw()
                {
                    return ("Error: Grade cannot be lower\n");
                }
        }; 
};

std::ostream& operator<<(std::ostream& os,const Bureaucrat& Other);

#endif