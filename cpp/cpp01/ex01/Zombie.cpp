










#include "Zombie.hpp"

Zombie::Zombie(std::string zombie_name)
{
    name = zombie_name;
}

Zombie::Zombie()
{}

Zombie::~Zombie()
{
    std::cout << name << " is destroyed." << std::endl;
}

void Zombie::announce(void)
{
    std::cout << name << ": " << " BraiiiiiiinnnzzzZ..." << std::endl;
}