template
    Template is a simple and yet very powerful tool in C++,
    with a simple idea, pass a data type as a parameter
    (generics types) so we don't need to write the same code for diff data types. like making a sort() function for diff data types rather than writing and maintaining multiple codes.

so generics types is the idea of passing data types as a parameter, and template is the tool or parameter in c++ to implement this idea.

function tamplate>:

we have template parameters that is a special kind of param
that can be used to pass a type as argument just like regular func template param allow to pass type to a function and these func tamplate can use these param
as if they were any other regular type.

the syntax for declaring function template:

template <class identifier> function_declaration;
template <typename identifier> function_declaration;

cpp```
{
    template <class myType>
    myType GetMax (myType a, myType b) {
    return (a>b?a:b);
}
}
```
Here we have created a template function with myType as its template parameter. This template parameter represents a type that has not yet been specified, but that can be used in the template function as if it were a regular type.

To use this function template we use the following format for the function call:

function_name <type> (parameters);

to call GetMax to compare two integer values of the same type we can write:

cpp```
{
    int x, y;
    std::cout << GetMax <int> (x=10,y=15) << "\n";
    // or
    double i, j;
    std::cout << GetMax <double> (i=13, j=39.8) << "\n";
    std::string str1 = "hello";
    std::string str2 = "wborld";
    std::cout << GetMax <std::string> (str1, str2) << "\n";
    // or this shulde set err
    // std::cout <<GetMax <std::string> (x, j) << "\n";
}
```

When the compiler see this call to a template function(the syntax above) , it uses the template to automatically generate a function replacing each appearance of myType in the func template by the type passed as the actual template parameter (int, double, string in this case) and then calls it.

This process is automatically performed by the compiler and is invisible to the programmer.

cpp```
{
    // function template
    #include <iostream>
    using namespace std;

    template <class T>
    T GetMax (T a, T b) {
    T result;
    result = (a>b)? a : b;
    return (result);
    }

    int main () {
    int i=5, j=6, k;
    long l=10, m=5, n;
    k=GetMax<int>(i,j);
    n=GetMax<long>(l,m);
    cout << k << endl;
    cout << n << endl;
    return 0;
    }
}
```
in this example  The compiler has instantiated and then called each time the appropriate version of the function.

As you can see, the type T is used within the GetMax() template function even to declare new objects of that type:

cpp```
T result;
```
result will be an object of the same type as the parameters a and b when the function template is instantiated with a specific type.

important:

In this specific case where the generic type T is used as a parameter for GetMax the compiler can find out automatically which data type has to instantiate without having to explicitly specify it within angle brackets

template function_declaration;
template <class identifier> function_declaration;

{
    int i,j;
    GetMax (i,j);
}

Since both i and j are of type int, and the compiler can automatically find out that the template parameter can only be int. This implicit method produces exactly the same result

cpp```
// function template II
#include <iostream>
using namespace std;

template <class T>
T GetMax (T a, T b) {
  return (a>b?a:b);
}

int main () {
  int i=5, j=6, k;
  long l=10, m=5, n;
  k=GetMax(i,j);
  n=GetMax(l,m);
  cout << k << endl;
  cout << n << endl;
  return 0;
}
```

Because our template function includes only one template parameter (class T) and the function template itself accepts two parameters, both of this T type, we cannot call our function template with two objects of different types as arguments:

cpp```
{
    int i;
    long l;
    k = GetMax (i,l);
}
```

This would not be correct, since our GetMax function template expects two arguments of the same type, and in this call to it we use objects of two different types.

we can define func templates that accept 2 param,
simply by specifying more template parameters between the angle brackets
of diff types and returns an object of one of those 
param.