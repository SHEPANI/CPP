
#include "Weapon.hpp"


Weapon::Weapon(std::string type) 
{
    setType(type);
}
Weapon::~Weapon()
{
}

void Weapon::setType(std::string Newtype)
{
    _type = Newtype;
}

const std::string& Weapon::getType()
{
    return (_type);
}