/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:41:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 20:34:55 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    try
    {
        Bureaucrat a(137, "Bureaucrat1");
        std::cout << a;
        ShrubberyCreationForm Form1("realHome");
        a.signForm(Form1);
        a.executeForm(Form1);
        ShrubberyCreationForm Form2("fakeHome");
        a.dec_burGrade();
        std::cout << a ;
        a.signForm(Form2);
        a.executeForm(Form2);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    try
    {
        Bureaucrat b(46, "Bureaucrat2");
        b.inc_burGrade();
        std::cout << b;
        RobotomyRequestForm Form3("Robot1");
        b.signForm(Form3);
        b.executeForm(Form3);
        RobotomyRequestForm Form4("Robot2");
        b.dec_burGrade();
        b.dec_burGrade();
        std::cout << b ;
        b.signForm(Form4);
        b.executeForm(Form4);
        std::cout << "\n";
    }
    catch(std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }
    
    try
    {
        Bureaucrat c(4, "Bureaucrat3");
        c.inc_burGrade();
        std::cout << c;
        PresidentialPardonForm Form5("Pardon1");
        c.signForm(Form5);
        c.executeForm(Form5);
        PresidentialPardonForm Form6("Pardon2");
        c.dec_burGrade();
        c.dec_burGrade();
        std::cout << c ;
        c.signForm(Form6);
        c.executeForm(Form6);
        PresidentialPardonForm Form7("Pardon3");
        c.dec_burGrade();
        std::cout << c ;
        c.signForm(Form7);
        c.executeForm(Form7);
        std::cout << "\n";
    }
    catch(std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }


    try
    {
        Bureaucrat d(26, "Bureaucrat4");
        std::cout << d;
        PresidentialPardonForm Form8("Pardon4");
        d.signForm(Form8);
        d.executeForm(Form8);
        std::cout << "\n";

    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    try
    {
        Bureaucrat e(73, "Bureaucrat5");
        std::cout << e;
        RobotomyRequestForm Form9("Robot3");
        e.signForm(Form9);
        e.executeForm(Form9);
        std::cout << "\n";
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        Bureaucrat f(146, "Bureaucrat6");
        std::cout << f;
        PresidentialPardonForm Form10("Home");
        f.signForm(Form10);
        f.executeForm(Form10);
        std::cout << "\n";
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}