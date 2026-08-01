
#include <map>
#include <iostream>
int main()
{
    std::map<std::string, std::string> mp;

    mp["2002-10-10"] = "10";
    mp["2002-11-11"] = "10";
    mp["2002-12-08"] = "10";
    mp["2003-10-11"] = "10";
    std::string key = "2002-10-10";
    std::map<std::string, std::string>::iterator it = mp.find(key);

    if (it == mp.end())
    {
        it = mp.lower_bound(key);
        if (it == mp.begin())
        {
            std::cout << "out of range\n";
        }
        else
        {
            it--;
            std::cout << "Closest smaller key: " << it->first << "\n";
        }
    }
};