/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:41:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 16:29:39 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
    try{
        Bureaucrat a;
        std::cout << a;
        Form b;
        std::cout << b;
        a.signForm(b);        
        std::cout << b << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }
   
    try{
        Bureaucrat a(15, "ahmed");
        std::cout << a;
        Form b("Form1", 10,13);
        std::cout << b;
        a.signForm(b);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    try{
        Bureaucrat a(13, "Mohamed");
        std::cout << a;
        Form b("Form2", 13,13);
        std::cout << b;    
        a.signForm(b);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    try{
        Bureaucrat a(100, "Mohamed");
        std::cout << a;
        Form b("Form2", 151,13);
        std::cout << b;    
        a.signForm(b);
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    try{
        Bureaucrat a(100, "Mohamed");
        std::cout << a;
        Form b("Form2", 0,13);
        std::cout << b;    
        a.signForm(b);
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    return 0;
}