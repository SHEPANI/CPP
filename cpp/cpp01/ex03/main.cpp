



#include <iostream>
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
    {
        Weapon club("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("ak-47");
        bob.attack();
    }
    {
        Weapon club = Weapon("crude spiked club");
        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("bfg9000");
        jim.attack();
    }
    return 0;
}