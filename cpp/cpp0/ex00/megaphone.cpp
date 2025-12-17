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
	int i = 1;
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	while(i < ac)
	{
		int j = 0;
		std::string str = av[i];
		while (str[j])
		{
			if (std::islower(str[j]))
				std::cout << (char)std::toupper(str[j]);
			else
				std::cout << str[j];
			j++;
		}
		i++;
	}
	std::cout << std::endl;
}