#include "BitcoinExchange.hpp"


int main(int c, char* av[])
{
    try 
    {
        if (c != 2)
            throw "Error: could not open file.";

        std::string filename = av[1];  
        std::ifstream ifile(filename.c_str());
    
        if (!ifile.is_open())
            throw "Error: could not open file.";
        

        BitcoinExchange a;        
        a.getBtcVal(ifile);

    }
    catch (const char *error)
    {
        std::cout << error << "\n";
    }
}