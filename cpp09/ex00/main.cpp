#include "BitcoinExchange.hpp"


int main(int c, char* av[])
{
    if (c != 2)
        std::cout << "usage format: ./btc <arg>\n";
    std::string filename = av[1];
 try 
 {

 
    if (filename.empty())
        throw "Error: empty_string\n";
    
    std::ifstream ifile(filename.c_str());

    if (!ifile.is_open())
        throw "Error: could not open file.\n";

    std::stringstream buffer;
    buffer << ifile.rdbuf();
    std::string content = buffer.str();
    ifile.close();
 }
 catch (char *err)
 {
    std::cout << err;
 }
}