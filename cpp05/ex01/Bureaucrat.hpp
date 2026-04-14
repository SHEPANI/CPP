/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:26:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 20:35:44 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream> // why string is built her
#include <string>
#include <ostream>
#include <exception>
#include "Form.hpp"

class Bureaucrat
{
    private:

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
        void inc_burGrade();  
        void dec_burGrade();
        void signForm(Form& form);
    
        class GradeTooHighException : public std::exception
        {
            public :
                const char* what() const throw()
                {   
                }
        };

        class GradeTooLowException : public std::exception
        {
            private :
                const char* what() const throw()
                {
                }
        }; 
};

std::ostream& operator<<(std::ostream& os,const Bureaucrat& Other);

#endif