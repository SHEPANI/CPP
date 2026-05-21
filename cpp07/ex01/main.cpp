
#include "iter.hpp"

void add(int &number)
{
    number+=1;
}

int main()
{
   int intArr[] = {1,2,3,4};
   std::string strArr[] = {"ahmed", "30 ans", "Casablanca"};

    std::cout << "------ printArrElement function ------\n";

   std::cout << "int Array element : ";
   iter(intArr, 4, printArrElement<int>);
   std::cout << "\n";

   std::cout << "str Array element: ";
   iter(strArr, 3, printArrElement<std::string>);
   std::cout << "\n";
   
   std::cout << "------ printArrElement function ------\n";

   std::cout << "int Array element : ";
   iter(intArr, 4, add);
   for (int i = 0; i < 4; i++)
        std::cout << intArr[i] << " ";
   std::cout << "\n";
    
}