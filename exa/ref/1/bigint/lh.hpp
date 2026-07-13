#include <iostream>
#include <sstream>


// class bigint
// {
//         std::string store;
//         void remove_zeros();
//         std::string add_string(const std::string& a , const std::string& b);
//         unsigned long long from_string(const std::string& s);
//     public:
//         bigint(); 
//         // default constructre
//         bigint(const std::string& bigs); 
//         // string parametraized constructer
//         bigint(unsigned long long bign); 
//         // unsigned long long para constructer
//         bigint(const bigint& Other); 
//         // copy constructer
//         bigint& operator=(const bigint& Other); 
//         // copy asignment constructer
//         ~bigint(); 
//         // desctructer

//          // +, +=, ++, ++ overloading operators 
//         bigint operator+(const bigint& Other) const;
//         bigint& operator+=(const bigint& Other);
//         bigint& operator++();
//         bigint operator++(int);

//         // >> , << operators
//         bigint& operator<<(const bigint& Other) const;  
//         bigint& operator>>(const bigint& Other) const;
    
//         // != , == , <=, => , < , > operators
//         bool operator!=(const bigint& Other); 
//         bool operator==(const bigint& Other);
//         bool operator<=(const bigint& Other);
//         bool operator<(const bigint& Other);
//         bool operator>=(const bigint& Other);
//         bool operator>(const bigint& Other);

//         friend std::ostream &operator<<(std::ostream &ss, const bigint& obj);
// };


#include <iostream>
#include <sstream>


class bigint
{
        // string to store number
        std::string storenum;
        //  func remove zeros
        void remove_zeros();
        // add strore num to another
        static std::string& add_str(const std::string& str1,const std::string& str2); 

        // i dont now way this func from_string
        unsigned long long strToNum(const std::string& strnum) const;
    public:
        // default constructre
        bigint();
        // string parametraized constructer
        bigint(const std::string& num);
        // unsigned long long para constructer
        bigint(unsigned long long num);
        // copy constructer
        bigint(const bigint& other);
        // copy asignment constructer
        bigint& operator=(const bigint& other);
        // desctructer
        ~bigint();

        // +, +=, ++, ++ overloading operators 
        bigint operator+(const bigint& other) const;
        bigint& operator+=(const bigint& other);
        bigint& operator++();
        bigint operator++(int);

        // >> , << operators
        bigint operator<<(const bigint& other) const;
        bigint operator>>(const bigint& other) const;
        bigint& operator<<=(const bigint& other);
        bigint& operator>>=(const bigint& other);

    
        // != , == , <=, => , < , > operators
        bool operator!=(const bigint& other) const;
        bool operator==(const bigint& other) const ;
        bool operator<=(const bigint& other) const;
        bool operator>=(const bigint& other) const;
        bool operator>(const bigint& other) const;
        bool operator<(const bigint& other) const;
        
        
};

        //  stream insertion operator
std::ostream& operator<<(std::ostream& ss, bigint& obj);