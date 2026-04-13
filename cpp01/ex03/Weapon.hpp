/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:13:10 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/11 19:08:40 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon 
{
    public:
        Weapon(std::string Newtype);
        ~Weapon();
        const std::string& getType();
        void setType(std::string Newtype);
    private:
        std::string type;
};
#endif