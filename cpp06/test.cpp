// ----- Implicit conversion ---

/*

Implicit conversions do not require any operator.
They are automatically performed when a value is copied
to a compatible type.

*/

/*

int main()
{
    short a = 100; 
    int b;
    b = a; // the value of a has been promoted from short to int
           // and we have not had to specify any type-casting operator.
           // This is known as a "standard conversion".
}

*/

/*
Implicit conversions also include constructor or operator conversions,
which affect classes that include specific constructors or operator 
functions to perform conversions. For example:
*/

/*
#include <iostream>
class a
{
    public:
        a(){
            std::cout << "a constructer\n";
        }
};
class b
{
    public:
        b (a A){
            std::cout << "b constructer\n";
        }
};

int main()
{
    a A;
    b B(A);
}

*/



/*
class a
{
    int i , j;
};

class b
{
    public: 
        float b , c;
};
int main()
{
    a * p ;
    b i;

    p = (a*)&i;
    a &rff = (a&)i;
}

*/

#include <iostream>
using namespace std;

class CDummy {
    float i=23,j=4;
};

class CAddition {
	int x,y;
  public:
	CAddition (int a, int b) { x=a; y=b; }
	int result() { return x+y;}
};

int main () {
  CDummy *d;
  CDummy a;
  d = &a;
  CAddition * padd;
  padd = (CAddition*) &d;
  cout << padd->result();
  return 0;
}