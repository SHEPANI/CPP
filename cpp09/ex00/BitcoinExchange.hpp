#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <stdlib.h>

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
        std::string strim(const std::string& ip);
        void createMapDb(void);
        void getBtcVal(std::ifstream& inpuText);
        int parseInput(std::string& iKey,std::string& iVal);
};

#endif