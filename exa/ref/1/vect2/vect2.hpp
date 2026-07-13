#include <string>
#include <iostream>
#include <algorithm>

class vect2
{
    private:
        int _x;
        int _y;
    public :
        vect2();
        vect2(const  vect2 &o);
        vect2(int x, int y);
        vect2 &operator=(const vect2 &o);

        int &operator[](int index);
        int operator[](int index) const;

        vect2 &operator+=(const vect2 &o);
        vect2 &operator-=(const vect2 &o);
        vect2 &operator*=(int scale);

        vect2 &operator++();
        vect2 operator++(int);
        vect2 &operator--();
        vect2 operator--(int);

        vect2 operator+(const vect2 &o) const;
        vect2 operator-(const vect2 &o) const;
        vect2 operator-() const;
        vect2 operator*(int scal) const;
        bool operator==(const vect2 &o) const;
        bool operator!=(const vect2 &o) const;
       friend vect2 operator*(int scal, const vect2 &o);

};

std::ostream &operator<<(std::ostream &s, const vect2 &o);