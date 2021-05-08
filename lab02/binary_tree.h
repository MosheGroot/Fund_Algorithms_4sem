#pragma once

#include <memory>
#include "comparators.h"

/* TREE NODE */
template<typename T> class binary_tree; //forward declaring

template<typename T>
class tree_node
{
friend class binary_tree;

private:
	T			data;
	tree_node*	left;
	tree_node*	right;

public:
	tree_node(T &value)
		: data(value), left(nullptr), right(nullptr)
	{}

	~tree_node(T& value)
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}
};

/* ABSTRACT TREE */
template<typename T>
class binary_tree
{
private:
	tree_node<T>*					root;
	std::shared_ptr<Comparator<T>>	cmp;

public:
	binary_tree(std::shared_ptr<Comparator<T>>& comparator)
		: root(nullptr), cmp(comparator)
	{}

	~binary_tree() {}

	void	set_comparator(std::shared_ptr<Comparator<T>>& comparator)
	{
		cmp = comparator();
	}

	virtual void	push(T value) = 0;
	virtual void	pop(T value) = 0;
	virtual bool	search(T value) = 0;
};

/* RED-BLACK TREE */

template<typename T>
class rb_tree : public binary_tree<T>
{
public:


};