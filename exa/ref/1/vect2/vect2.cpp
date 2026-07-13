#include "vect2.hpp"



        vect2::vect2() : _x(0), _y(0)
        {

        }
        vect2::vect2(const  vect2 &o): _x(o._x), _y(o._y)
        {

        }
        vect2::vect2(int x, int y) : _x(x), _y(y)
        {

        }
        vect2 &vect2::operator=(const vect2 &o)
        {
            if(this != &o)
            {
                _x = o._x;
                _y = o._y;
            }
            return *this;
        }

        int &vect2::operator[](int index)
        {
            return (index == 0) ? _x : _y;
        }
        int vect2::operator[](int index) const
        {
            return (index == 0) ? _x : _y;
        }

        vect2 &vect2::operator+=(const vect2 &o)
        {
            _x = _x + o._x;
            _y = _y + o._y;
            return *this;
        }
        vect2 &vect2::operator-=(const vect2 &o)
        {
            _x = _x - o._x;
            _y = _y - o._y;
            return *this;
        }
        vect2 &vect2::operator*=(int scale)
        {
            _x = _x * scale;
            _y = _y * scale;
            return *this;
        }

        vect2 &vect2::operator++()
        {
            ++_x;
            ++_y;
            return *this;
        }
        vect2 vect2::operator++(int)
        {
            vect2 t(*this);
            ++(*this);
            return t;
        }

        vect2 &vect2::operator--()
        {
            --_x;
            --_y;
            return *this;
        }
        vect2 vect2::operator--(int)
        {
            vect2 t(*this);
            --(*this);
            return t;
        }


        vect2 vect2::operator+(const vect2 &o) const
        {
            return vect2(_x + o._x, _y +  o._y);
        }
        vect2 vect2::operator-(const vect2 &o) const
        {
            return vect2(_x - o._x, _y -  o._y);

        }
        vect2 vect2::operator-() const
        {
            return vect2(-_x, -_y);

        }
        vect2 vect2::operator*(int scal) const
        {
            return vect2(_x * scal, _y * scal);

        }
       vect2 operator*(int scal, const vect2 &o)
       {
            return vect2(o._x * scal, o._y * scal);
       }
        bool vect2::operator==(const vect2 &o) const
        {   
            return _x == o._x && _y == o._y;
        }
        bool vect2::operator!=(const vect2 &o) const
    {
        return !(*this == o);
    }
std::ostream &operator<<(std::ostream &s, const vect2 &o)
{
    s << "{" << o[0] << ", " << o[1] << "}";
    return s; 
}
