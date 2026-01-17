/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:50:43 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/17 18:38:12 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
 
class Fixed
{
    private:
        int _fixed;
        static const int _fraction = 8;
    public:
        Fixed();
        Fixed(const Fixed& fixOther);
        Fixed& operator=(const Fixed& fixOther);
        ~Fixed();
        int getRawBits(void) const;
        void setRawBits(int const raw);
};
