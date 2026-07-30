#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : dbtext("data.csv")
{
    createMapDb();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    if (&other != this)
    {
        *this = other;
    }
}

const BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (&other != this)
    {
        *this = other;
    }
    return *this;
}

void BitcoinExchange::createMapDb(void)
{
    
    for (std::string line; std::getline(dbtext, line);)
    {
        std::istringstream iss(line);

        std::string key,val;
        
        if (std::getline(iss, key, ','))
        {
            if (std::getline(iss, val, ','))
                dbmap.insert(std::make_pair(key, val));
        }
    }
}

void BitcoinExchange::getBtcVal(std::ifstream& inpuText)
{
    for (std::string line; std::getline(inpuText, line);)
    {
        if (line.empty()) continue;
        std::istringstream iss(line);

        std::string date,mVal;
        
        if (std::getline(iss, date, '|'))
            date.erase(date.length() -1);

        if (std::getline(iss, mVal, '|'))
            mVal.erase(mVal.begin());
        std::cout << "date : " << date << " , Mvale = " << mVal << "\n";
    }
}


BitcoinExchange::~BitcoinExchange(){};

