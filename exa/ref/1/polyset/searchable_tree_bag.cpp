#include "searchable_tree_bag.hpp"
#include "tree_bag.hpp"

    searchable_tree_bag::searchable_tree_bag() : tree_bag()
    {

    }
    searchable_tree_bag::~searchable_tree_bag()
    {

    }
    searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &o) : tree_bag(o)
    {

    }
    searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &o)
    {
        if(this != &o)
        {
            tree_bag::operator=(o);
        }
        return *this;
    }
    bool searchable_tree_bag::search_tree(node *n, int v) const
    {
        if(!n)
            return false;
        if(n->value == v)
            return true;
        if(n->value > v)
            return search_tree(n->l, v);
        else
            return search_tree(n->r , v);
    }

	bool searchable_tree_bag::has(int v) const
    {
        return search_tree(tree, v);
    }
