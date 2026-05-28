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