





#include "Zombie.hpp"

int main() {
    Zombie* newZombie_horde("hello");
    newZombie_horde->announce();
    delete[] newZombie_horde;
    return 0;
}