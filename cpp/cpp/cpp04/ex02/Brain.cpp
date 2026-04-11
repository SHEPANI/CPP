/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:33:19 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 02:33:20 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <iostream>

Brain::Brain()
{
    std::cout << "Brain Default Constructor called" << std::endl;
}

Brain::Brain(const Brain& Other)
{
    std::cout << "Brain Copy Constructor called" << std::endl;
    *this = Other;
}

Brain& Brain::operator=(const Brain& Other)
{
    std::cout << "Brain Copy Assignment Operator called" << std::endl;
    if (this != &Other)
    {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = Other.ideas[i];
    }
    return *this;
}

Brain::~Brain()
{
    std::cout << "Brain Destructor called" << std::endl;
}

std::string Brain::getIdea(int i) const
{
    if (i < 0 || i >= 100)
        return "";
    return ideas[i];
}

void Brain::setIdea(int i, const std::string& idea)
{
    if (i >= 0 && i < 100)
        ideas[i] = idea;
}