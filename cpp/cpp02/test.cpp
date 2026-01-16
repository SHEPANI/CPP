

//------------------------------------------------------------------------------------------------------------------

// ------- he copy constructor -----------

// A copy constructor is a constructor that is used to initialize an object
// with an existing object of the same type. After the copy constructor executes,
// the newly created object should be a copy of the object passed in as the initializer.


// -------------- An implicit copy constructor ----------

// If you do not provide a copy constructor for your classes,
// C++ will create a public implicit copy constructor for you

// #include <iostream>

// class Fraction
// {
// private:
//     int m_numerator{ 0 };
//     int m_denominator{ 1 };

// public:
//     // Default constructor
//     Fraction(int numerator=0, int denominator=1)
//         : m_numerator{numerator}, m_denominator{denominator}
//     {
//     }

//     void print() const
//     {
//         std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
//     }
// };

// int main()
// {
//     Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
//     Fraction fCopy { f }; // What constructor is used here?

//     f.print();
//     fCopy.print();

//     return 0;
// }

// By default, the implicit copy constructor will do memberwise initialization.
//  This means each member will be initialized using the corresponding member 
//  of the class passed in as the initializer. In the example above, 
//  fCopy.m_numerator is initialized using f.m_numerator (which has value 5), 
// and fCopy.m_denominator is initialized using f.m_denominator (which has value 3).

//  ------ So C++ explicitly allows:

// Member functions can access private members of any object of the same class.
// This means the member functions of a class can access the private members of 
// any class object of the same type (not just the implicit object).

// ---- Best practice --------

// Copy constructors should have no side effects beyond copying.
// A copy constructor must only copy state, because the compiler may 
// skip calling it entirely.

// ----------- The copy constructor’s parameter must be a reference ----

// It is a requirement that the parameter of a copy constructor be an lvalue
//  reference or const lvalue reference. Because the copy constructor should not
//   be modifying the parameter, using a const lvalue reference is preferred.

// ------------ Pass by value and the copy constructor ---------

// When an object is passed by value, the argument is copied into the parameter. 
// When the argument and parameter are the same class type,
//  the copy is made by implicitly invoking the copy constructor.

// #include <iostream>

// class Fraction
// {
// private:
//     int m_numerator{ 0 };
//     int m_denominator{ 1 };

// public:
//     // Default constructor
//     Fraction(int numerator = 0, int denominator = 1)
//         : m_numerator{ numerator }, m_denominator{ denominator }
//     {
//     }

//     // Copy constructor
//     Fraction(const Fraction& fraction)
//         : m_numerator{ fraction.m_numerator }
//         , m_denominator{ fraction.m_denominator }
//     {
//         std::cout << "Copy constructor called\n";
//     }

//     void print() const
//     {
//         std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
//     }
// };

// void printFraction(Fraction f) // f is pass by value
// {
//     f.print();
// }

// int main()
// {
//     Fraction f{ 5, 3 };

//     printFraction(f); // f is copied into the function parameter using copy constructor

//     return 0;
// }



// ---------------------------- Copy assignment vs Copy constructor -----


// The purpose of the copy constructor and the copy assignment operator are almost equivalent
// -- both copy one object to another. However, the copy constructor initializes new objects,
//  whereas the assignment operator replaces the contents of existing objects.

// The difference between the copy constructor and the copy assignment operator causes
//  a lot of confusion for new programmers, but it’s really not all that difficult.
//   Summarizing:

// If a new object has to be created before the copying can occur,
// the copy constructor is used (note: this includes passing or returning objects by value).
// If a new object does not have to be created before the copying can occur,
// the assignment operator is used.


// ----------------------------------------------

// Why int alone can’t do fractional math

// If you store 5 as 5 and 2.5 as int 2 → 2.5 is gone

// 5 + 2.5 → 5 + 2 = 7 ❌ Wrong

// Fixed-point solves this by scaling everything by 256

// 4️⃣ Why float alone can do math

// Floats can already represent fractions

// You don’t need scaling

// But:

// Slower on microcontrollers / old CPUs

// Slight rounding errors

// Non-deterministic sometimes (e.g., same operation may give slightly different results on different CPUs)

// ✅ So in many embedded systems or old games, fixed-point is preferred for speed and predictability.


// ------------ Explanation: ---------- 

// This program overloads the >> and << operators to allow easy input and output
// 0f Complex objects. It uses friend functions to access private members 
// and format input/output like built-in types.

// Rules for Stream Operators Overloading
// When overloading stream operators, the following rules must be followed:

// Always return the stream (ostream& or istream&) by reference to allow chaining of multiple input/output operations.
// Pass both the stream and the object by reference to avoid unnecessary copying.
// Declare the parameter as const in the insertion operator (<<) since output operations do not modify the object.
// Implement the operator as a non-member function, but declare it as a friend if access to private members is required.

//----------------------------------------------------------------------------
