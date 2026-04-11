#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0; // Pure virtual function
    virtual ~Shape()
    {};
};

class Circle : public Shape {
public:
    void draw()  {
        cout << "Drawing Circle\n";
    }
};

int main() {
    
    // Error in the below line : Cannot create 
    // object of abstract class
    // Shape s;      
    
    // Pointer to abstract class
    Shape* s = new Circle(); 
    
    // Output: Drawing Circle
    s->draw();    
    
    delete s;
}