#include <string>
#include <iostream>

class vect2
{
    private :
        int _x;
        int _y;
    public :
        vect2();
        vect2(const vect2 &obj);
        vect2(int x, int y);
        vect2 &operator=(const vect2 &obj);
        ~vect2();

        int operator[](int val) const;
        int &operator[](int val);

        vect2 operator++(int); // ++v
        vect2 &operator++(); // v++
        vect2 operator--(int); // ++v
        vect2 &operator--(); // v++

        vect2 operator+(const vect2 &obj) const;
        vect2 operator-(const vect2 &obj) const;
        vect2 operator-() const;
        vect2 operator*(int val) const;
        friend vect2 operator*(int val, const vect2 &obj);

        vect2 &operator+=(const vect2 &obj);
        vect2 &operator-=(const vect2 &obj);
        vect2 &operator*=(int val);

        bool operator==(const vect2 &obj) const;
        bool operator!=(const vect2 &obj) const;
};

std::ostream &operator<<(std::ostream &out, const vect2 &obj);