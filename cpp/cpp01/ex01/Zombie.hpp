
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP


#include <string>
#include <iostream>

class Zombie {
private:
    std::string name;
public:
    Zombie();
    void announce(void);
    ~Zombie();
    Zombie(std::string zombie_name);
};

Zombie* zombieHorde(int N, std::string name);

#endif