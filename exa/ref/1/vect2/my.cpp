#include "my.hpp"

vect2::vect2() : _x(0), _y(0)
{}

vect2::vect2(const vect2 &obj)
{
    _x = obj._x;
    _y = obj._y;
}

vect2::vect2(int x, int y)
{
    _x = x;
    _y = y;
}

vect2 &vect2::operator=(const vect2 &obj)
{
    if(this != &obj)
    {
        _x = obj._x;
        _y = obj._y;
    }
    return (*this);
}

vect2::~vect2()
{}

int vect2::operator[](int val) const
{   
    if(val == 0)
        return _x;
    else 
        return _y;
}

int &vect2::operator[](int val)
{
    if(val == 0)
        return _x;
    else 
        return _y;
}

vect2 &vect2::operator++()
{
    _x++;
    _y++;
    return *this;
}

vect2 vect2::operator++(int)
{
    vect2 tmp(*this);
    ++(*this);
    return tmp;
}

vect2 &vect2::operator--()
{
    _x--;
    _y--;
    return *this;
}

vect2 vect2::operator--(int)
{
    vect2 tmp(*this);
    --(*this);
    return tmp;
}

vect2 vect2::operator+(const vect2 &obj) const
{
    return (vect2(_x + obj._x, _y + obj._y));
}
vect2 vect2::operator-(const vect2 &obj) const
{
    return (vect2(_x - obj._x, _y - obj._y));

}

vect2 vect2::operator-() const
{
    return (vect2(-_x, -_y));
}

vect2 vect2::operator*(int val) const
{
    return (vect2(_x * val, _y * val));

}

vect2 operator*(int val, const vect2 &obj)
{   
    return (vect2(val * obj._x, val * obj._y));
}

vect2 &vect2::operator+=(const vect2 &obj)
{
    *this = *this + obj;
    return *this;
}
vect2 &vect2::operator-=(const vect2 &obj)
{
    *this = *this - obj;
    return *this;
}
vect2 &vect2::operator*=(int val)
{
    *this = *this * val;
    return *this;
}

bool vect2::operator==(const vect2 &obj) const
{
    if(_x == obj._x && _y == obj._y)
        return true;
    return false;
}   

bool vect2::operator!=(const vect2 &obj) const
{
    return !(*this == obj);
}

std::ostream &operator<<(std::ostream &out, const vect2 &obj)
{
    out << "{" << obj[0] << ", " << obj[1] << "}";
    return out;
}
