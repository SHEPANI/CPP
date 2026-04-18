/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:41:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 14:07:47 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
    Bureaucrat a(2, "ahmed");
    std::cout << "a : " << a << "\n";

    Bureaucrat b;
    b = a;
    b.dec_burGrade();
    std::cout << "b : " << b << "\n";

    Bureaucrat c(a);
    c.inc_burGrade();
    std::cout << "c : "<< c << "\n";

    try
    {
        std::cout << a;
        a.inc_burGrade();
        std::cout << a;
        a.inc_burGrade();
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    try
    {
        Bureaucrat b(145, "Robot");
        std::cout << b;
        for (int i = 0; i < 15; i++)
            b.dec_burGrade();
        std::cout << b;        
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    try
    {
        std::cout << c;
        c.inc_burGrade();
        std::cout << c;
        c.inc_burGrade();
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what() << "\n";
    }

    return 0;
}