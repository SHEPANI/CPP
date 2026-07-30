#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

class BitcoinExchange
{
    private:
        std::ifstream dbtext;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        const BitcoinExchange&  operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        std::map<std::string, std::string> dbmap;
        void createMapDb(void);
        void getBtcVal(std::ifstream& inpuText);
};

#endif