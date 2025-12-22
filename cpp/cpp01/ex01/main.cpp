





#include "Zombie.hpp"

int main() {
    Zombie* newZombie_horde = zombieHorde(3 , "Bar");
    newZombie_horde->announce();
    delete[] newZombie_horde;
    return 0;
}