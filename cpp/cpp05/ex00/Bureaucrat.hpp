/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:26:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/26 11:44:29 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <iostream> // why string is builting her
#include <string>
#include <ostream>

class Bureaucrat
{
    protected:
        const std::string name;
        unsigned int   grade;
    public:
        Bureaucrat();
        Bureaucrat(unsigned int newGrade);
        Bureaucrat(const Bureaucrat& Other);
        Bureaucrat& operator=(const Bureaucrat& Other);
        ~Bureaucrat();

        const std::string& getName() const;
        int getGrade() const;
        void inc_burGrade(int inc_grade);
        void dec_burGrade(int dec_grade);
};

std::ostream& operator<<(std::ostream& os,const Bureaucrat& Other);