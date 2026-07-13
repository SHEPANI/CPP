#include "Array.hpp"

int main()
{
    Array <int> emptyArray;
    std::cout << "size of empty Array : " << emptyArray.size() << "\n";
    Array <int> arrayWithElemets(12);
    std::cout << "size of Array with 12 elements : " << arrayWithElemets.size() << "\n";
    Array <int> copyCstrObjOfArray = arrayWithElemets;
    std::cout << "size of the copy constructer Array with 12 elements : " << copyCstrObjOfArray.size() << "\n";
    Array <int> copyOperObjOfArray;
    copyOperObjOfArray = arrayWithElemets;
    std::cout << "size of the copy constructer Array with 12 elements : " << copyOperObjOfArray.size() << "\n";
    std::cout << "size of Array with 12 elements : " << arrayWithElemets.size() << "\n";
    arrayWithElemets.operator[](11) = 10;
    std::cout << arrayWithElemets.operator[](11) << "\n";

    std::cout << "\n------------ arrayWithElemets ----------\n" ;    

    try
    {
        std::cout << arrayWithElemets.operator[](12);
    }
    catch(const std::exception& e)
    {
        std::cerr << "acces arrayWithElemets error : " << e.what() << " max size is "
        << arrayWithElemets.size() << '\n';
    }

    std::cout << "\n------------ constArrayWithElements ----------\n" ;


    const Array <int> constArrayWithElements(13);
    try
    {
        for (int i = 0; i < 37; i++)
            std::cout << constArrayWithElements.operator[](i) << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "acces constArrayWithElements error : " << e.what() << " max size is "
        << constArrayWithElements.size() << '\n';
    }

    std::cout << "\n------------ arrayWithMoreElemets ----------\n" ;

    Array <int> arrayWithMoreElemets(37);
    for (int i = 0; i < 37; i++)
        arrayWithMoreElemets.operator[](i) = i;
    try
    {
        for (int i = 0; i < 37; i++)
            std::cout << arrayWithMoreElemets[i] << "\n";
        arrayWithMoreElemets[37] = 13;
    }
    catch(const std::exception& e)
    {
        std::cerr << "acces arrayWithMoreElemets error : " << e.what() << " max size is "
        << arrayWithMoreElemets.size() << '\n';
    }
}