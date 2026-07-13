
STL (standard template library) is a cpp standard library
its conataine to portucalary things

first one is conatiners: its a generic containers templates wich enable
to containe anything in very good emplementation if u wanna use as programmer 
algorithams u can use STL containers or a container made ur self

----------------------------------------------------







In C++, a MutantStack is a popular custom data structure designed to fix a major limitation of std::stack.While the standard std::stack is a container adapter that limits your access strictly to the LIFO (Last-In, First-Out) interface (push(), pop(), top()), it intentionally hides the ability to iterate through its elements. A MutantStack solves this by inheriting from std::stack and exposing the underlying container's iterators
nder the hood, std::stack stores its elements inside a protected member variable named c (which defaults to a std::deque). Because c is marked as protected inside std::stack rather than private, any class that inherits from std::stack can directly access it.