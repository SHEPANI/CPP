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

std::string BitcoinExchange::strim(const std::string& val)
{
    size_t end = val.size();
    size_t start = 0;

    while (start < end && std::isspace(val[start]))
    {
        start++;
    }

    while (end > start && std::isspace(val[end -1]))
    {
        end--;
    }
    return val.substr(start, end - start);
}


void BitcoinExchange::getBtcVal(std::ifstream& inpuText)
{
    std::string line;
    while (std::getline(inpuText, line))
    {
        line = strim(line);
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string indate,inVal;
        
        std::getline(iss, indate, '|');
        std::getline(iss, inVal, '|');
    
        indate = strim(indate);
        inVal = strim(inVal);
        if (indate == "date" && inVal == "value")
            continue;
        if (parseInput(indate, inVal))
        {
            std::map<std::string, std::string>::iterator it = dbmap.find(indate);

            if (it == dbmap.end())
            {

                it = dbmap.lower_bound(indate);
                if (it == dbmap.begin())
                    std::cerr << "Error: bad input => " << indate << "\n";
                else
                {
                    it--;
                    std::stringstream ss(it->second);
                    double dbValNum = 0;
                    ss >> dbValNum;
                    ss.clear();
                    ss.str("");
                    double inMultiNum = 0;
                    ss << inVal;
                    ss >> inMultiNum;
                    std::cout << indate << " => " << inVal << " = "<< dbValNum * inMultiNum << "\n";

                }
            }
            else
            {
                std::stringstream ss(it->second);
                double dbValNum = 0;
                ss >> dbValNum;
                ss.clear();
                ss.str("");
                double inMultiNum = 0;
                ss << inVal;
                ss >> inMultiNum;
                std::cout << indate << " => " << inVal << " = "<< dbValNum * inMultiNum << "\n";
            }
        }
    }
}

int BitcoinExchange::parseInput(std::string& iKey,std::string& iVal)
{
    int dash = 0;
    int dayMax = 31;
    int dot = 0;
    int valSize = iVal.size();
    int keySize = iKey.size();
    std::stringstream ss(iVal);
    double valNum;
    
    if (keySize != 10)
        return (std::cerr << "Error: bad input => " << iKey << "\n", false);

    for (int i = 0; i < keySize; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(iKey[i]))
            return (std::cerr << "Error: bad input => " << iKey << "\n", false);
    }

    if (iKey[4] == '-' && iKey[7] == '-')
        dash = 2;

    int day = std::atoi(iKey.substr(8, 2).c_str());
    int month = std::atoi(iKey.substr(5, 2).c_str());
    int yr = std::atoi(iKey.substr(0, 4).c_str());

    if (dash != 2 || iKey.empty() || yr < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return (std::cerr << "Error: bad input => " << iKey << "\n", false);
    else if (month == 11 || month == 9 || month == 6 || month == 4)
        dayMax = 30;
    else if (month == 2)
    {
        bool leapYear = (yr % 4 == 0 && yr % 100 != 0) || (yr % 400 == 0);
        if (leapYear)
            dayMax = 29;
        else
            dayMax = 28;
    }

    if (day > dayMax)
        return (std::cerr << "Error: bad input => " << iKey << "\n", false);

    if (iVal.empty())
        return (std::cerr << "Error: bad input => " << iVal << "\n", false);

    for (int i = 0; i < valSize; i++)
    {
        if (iVal[i] == '.')
        {
            if (++dot > 1 || iVal[0] == '.' || iVal[valSize-1]=='.')
                return (std::cerr << "Error: bad input => " << iVal << "\n", false);
            continue;
        }
        if (!isdigit(iVal[i]))
        {
            if (i == 0 && (iVal[0] == '-' || iVal[0] == '+'))
                continue;
            return (std::cerr << "Error: bad input => " << iVal << "\n", false);
        }
    }

    if (!(ss >> valNum))
        return (std::cerr << "Error: too large a number. " << "\n", false);
    if (valNum < 0)
        return (std::cerr << "Error: not a positive number." << "\n", false);
    if (valNum > 1000)
        return (std::cerr << "Error: too large a number." << "\n", false);
    return true;
}

BitcoinExchange::~BitcoinExchange(){};

