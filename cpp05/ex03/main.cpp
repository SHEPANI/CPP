/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:41:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 22:50:09 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

int main()
{
    try
    {
        Bureaucrat a;
        Intern RandomInern1;
        AForm* form1;
        AForm* form2;
        form1 = RandomInern1.makeForm("presidential pardon", "Bender");
        form2 = RandomInern1.makeForm("fake presidential pardon", "Bender");
        (void)form2;
        a.signForm(*form1);
        a.executeForm(*form1);
        delete form1;
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    try
    {
        Bureaucrat b(1, "Leader");
        Intern RandomInern2;
        AForm* form3;
        AForm* form4;
        form3 = RandomInern2.makeForm("shrubbery creation", "Home");
        form4 = RandomInern2.makeForm("fake shrubbery creation", "Home");
        (void)form4;
        b.signForm(*form3);
        b.executeForm(*form3);
        std::cout << "\n";
        delete form3;
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    try
    {
        Bureaucrat c;
        Intern RandomInern3;
        AForm* form5;
        AForm* form6;
        form5 = RandomInern3.makeForm("robotomy request", "vegapunk");
        form6 = RandomInern3.makeForm("fake robotomy request", "vegapunk");
        (void)form6;
        c.signForm(*form5);
        c.executeForm(*form5);
        delete form5;
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }

    return 0;
}