/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:32:54 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 03:01:56 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


class Brain
{
    private:
        std::string ideas[100];
    public:
        Brain();
        Brain(const Brain& Other);
        Brain& operator=(const Brain& Other);
        ~Brain();
        
        std::string getIdea(int i);
        
}