





#include "Zombie.hpp"

int main() {
    Zombie *newZombie1;
    newZombie1 = newZombie("LHOUSSEINE");
    newZombie1->announce();
    randomChump("LHOUSSEINE");
    delete newZombie1;
    return 0;
}