/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:31:11 by lhchiban          #+#    #+#             */
/*   Updated: 2025/12/11 10:08:00 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < ac; i++)
	{
		std::string str = av[i];
		for (unsigned long j = 0; j < str.length(); j++)
		{
			if (std::islower(str[j]))
				std::cout << (char)std::toupper(str[j]);
			else
				std::cout << str[j];
		}
	}
	std::cout << std::endl;
	return (0);
}