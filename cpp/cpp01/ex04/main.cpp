
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void SetError(std::string ErrorType)
{
    if (ErrorType == "open")
        std::cout << "Error: could not open file." << std::endl;
    else if (ErrorType == "read")
        std::cout << "Error: could not read file." << std::endl;
    else if (ErrorType == "empty_string")
        std::cout << "Error: s1 is an empty string." << std::endl;
    else if (ErrorType == "arguments")
        std::cout << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 4)
        return (SetError("arguments"), 1);

    std::string filename = av[1];
    std::string s1 = av[2];
    std::string s2 = av[3];
    size_t pos = 0;

    if (s1.empty())
        return (SetError("empty_string"), 1);

    std::ifstream infile(filename.c_str());

    if (!infile.is_open())
        return (SetError("open"), 1);

    std::stringstream buffer;
    buffer << infile.rdbuf();
    std::string content = buffer.str();
    if (content.empty())
        return (SetError("read"), 1);
    infile.close();

    while ((pos = content.find(s1, pos)) != std::string::npos) {
        content.erase(pos, s1.length());
        content.insert(pos, s2);
        pos += s2.length();
    }

    std::ofstream outfile((filename + ".replace").c_str());
    if (!outfile.is_open())
        return (SetError("open"), 1);
    outfile << content;
    outfile.close();
    return 0;
}