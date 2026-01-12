

class Fixed
{
    private:
        int _fixed;
        static const int _fraction = 8;
    public:
        Fixed();
        Fixed(const Fixed& fixOther);
        Fixed& operator=(const Fixed& fixOther);
        ~Fixed();
        int getRawBits(void) const;
        void setRawBits(int const raw);
};
