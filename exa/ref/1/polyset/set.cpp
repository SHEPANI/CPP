#include "set.hpp"
#include "iostream"
void set::insert(int v)
{
    if(!bag.has(v))
        bag.insert(v);
}
void set::insert(int *array, int size) 
{
    for(int i = 0 ; i <= size; i++)
    {
        // std::cout << "here set" << std::endl;
        insert(array[i]);
    }
}
void set::print() const
{
    bag.print();
}
void set::clear()
{
    bag.clear();

}
set::set(searchable_bag &bagg) : bag(bagg)
{

}
searchable_bag &set::get_bag()
{
    return bag;
}


bool set::has(int c) const
{
    return bag.has(c);
}
