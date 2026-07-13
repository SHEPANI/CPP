#include "searchable_bag.hpp"
#include "tree_bag.hpp"


class searchable_tree_bag : public searchable_bag , public tree_bag
{
    public :
    searchable_tree_bag();
    ~searchable_tree_bag();
    searchable_tree_bag(const searchable_tree_bag &o);
    searchable_tree_bag &operator=(const searchable_tree_bag &o);

	bool has(int  v) const;
    private :
        bool search_tree(node *n, int v) const; 
};