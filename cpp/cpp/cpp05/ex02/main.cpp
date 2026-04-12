/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:41:27 by lhchiban          #+#    #+#             */
/*   Updated: 2026/04/12 18:28:38 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

int main()
{
    try
    {
        Bureaucrat a;
        a.inc_burGrade();
        std::cout << a;
        ShrubberyCreationForm B1("Home");
        a.signForm(B1);
        B1.execute(a);
    }
    catch (std::exception& e)
    {
        std::cout << "Custom Error Caught: " << e.what();
    }

    
    return 0;
}