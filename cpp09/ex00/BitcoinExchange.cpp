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
    std::string line;
    std::getline(dbtext, line);
    while (std::getline(dbtext, line))
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
    std::string line;
    std::getline(inpuText, line);
    while (std::getline(inpuText, line))
    {
        if (line.empty()) continue;
        std::istringstream iss(line);

        std::string indate,inVal;
        
        if (std::getline(iss, indate, '|'))
            indate.erase(indate.length() -1);
        
        if (std::getline(iss, inVal, '|'))
            inVal.erase(inVal.begin());

        if (parseInput(indate, inVal))
        {
            std::map<std::string, std::string>::iterator it = dbmap.find(indate);

            if (it != dbmap.end())
            {
                std::cout << "key not find\n";
            }
            else
            {
                std::cout << "key find\n";
            }
        }
    }
}

//Error: too large a number.
// Error: not a positive number.
// Error: bad input => 2001-42-42
int BitcoinExchange::parseInput(std::string& iKey,std::string& iVal)
{
    int dash = 0;
    int dot = 0;
    int valSize = iVal.size();
    std::stringstream ss(iVal);
    int valNum;

    for (int i = 0; i < 10; i++)
    {
        if (iKey[i] == '-')
            continue;
        if (!isalnum(iKey[i]))
            return (std::cout << "Error: bad input => " << iKey << "\n", false);
    }
    if (iKey[4] == '-' && iKey[7] == '-')
        dash = 2;
    if (dash != 2 || iKey[5] > (3 + '0')  || iKey[8] > (3 + '0') || iKey.empty())
        return (std::cout << "Error: bad input => " << iKey << "\n", false);

    if (iVal.empty())
        return (std::cout << "Error: bad input => " << iVal << "\n", false);

    for (int i = 0; i < valSize; i++)
    {
        if (iVal[i] == '.')
        {
            if (++dot > 1)
                return (std::cout << "Error: bad input => " << iVal << "\n", false);
            continue;
        }
        if (!isalnum(iVal[i]))
            return (std::cout << "Error: bad input => " << iVal << "\n", false);
    }

    if (!(ss >> valNum) || (valNum > 1000))
        return (std::cout << "Error: too large a number." << "\n", false);
    if (valNum < 0)
        return (std::cout << "Error: not a positive number. " << "\n", false);
    return true;
}

BitcoinExchange::~BitcoinExchange(){};

