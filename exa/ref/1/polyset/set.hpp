
#include "searchable_bag.hpp"
class set
{
    public :
    void insert(int v);
	void insert(int *array, int size) ;
	void print() const;
	void clear();
    set(searchable_bag &bagg);
    searchable_bag &get_bag();
    bool has(int c) const;
    private :
        searchable_bag &bag;
};