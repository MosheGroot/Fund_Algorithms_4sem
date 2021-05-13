#pragma once

#include <memory>
#include "comparators.h"

/* ABSTRACT TREE */
template<typename T>
class binary_tree
{
private:
	std::shared_ptr<Comparator<T>>	cmp;

public:
	binary_tree(const std::shared_ptr<Comparator<T>>& comparator)
		: root(nullptr), cmp(comparator)
	{}

	~binary_tree() {}

	void	set_comparator(const std::shared_ptr<Comparator<T>>& comparator)
	{
		cmp = comparator();
	}

	virtual void	push(const T& value) = 0;
	virtual void	pop(const T& value) = 0;
	virtual bool	search(const T& value) = 0;
};

/******************/
/* RED-BLACK TREE */
/******************/

/* RB_TREE NODE */
# define BLACK 0
# define RED 1

template<typename T> class rb_tree; //forward declaring

template<typename T>
class rb_tree_node
{
friend class rb_tree;

private:
	T					data;
	rb_tree_node<T>		*left;
	rb_tree_node<T>		*right;

	rb_tree_node<T>		*prev;
	unsigned char		color;

	rb_tree_node(T &value, const rb_tree_node<T> *prev)
		: data(value), left(nullptr), right(nullptr), prev(nullptr), color(RED)
	{}

	~rb_tree_node(T& value)
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}
};

template<typename T>
class rb_tree : public binary_tree<T>
{
public:
	rb_tree_node<T>		*root;

	/* BALANCE CHECK */
	static unsigned char	get_ncolor(rb_tree_node<T> *node)
	{
		if (!node || node->color = BLACK)
			return BLACK;
		return RED;
	}

	static inline void		balance_check_1(rb_tree_node<T> *grandfather, rb_tree_node<T> *child)
	{
		if (!grandfather || get_ncolor(grandfather) != BLACK || get_ncolor(child) != RED ||
			get_ncolor(grandfather->left) != RED || get_ncolor(grandfather->right) != RED)
			return;

		grandfather->color = RED;
		grandfather->left->color = BLACK;
		grandfather->right->color = BLACK;
	}

	static inline void		balance_check_2(rb_tree_node<T> *g)
	/* push */
	static inline void		add_node_as_child(const T& value, rb_tree_node<T> **child)
	{
		rb_tree_node<T>	*current = root;
		int cmp;
		while (true)
		{
			cmp = this->cmp(value, current->data);
			if (cmp < 0)
			{
				if (!current->left)
					current = current->left;
				else
				{
					current->left = new rb_tree_node<T>(value, current);
					*child = current->left;
					break;
				}
			}
			else if (cmp > 0)
			{
				if (!current->right)
					current = current->right;
				else
				{
					current->right = new rb_tree_node<T>(value, current);
					*child = current->right;
					break;
				}
			}
		}
	}

	virtual void	push(const T& value)
	{
		if (!root)
		{
			root = new rb_tree_node(T, nullptr);
			root->color = BLACK;
			return;
		}
		
		rb_tree_node<T> *added;
		rb_tree_node<T>	*father = add_node_as_child(value, &added);
		balance_check_1(father->prev, added);
		balance_check_2
	}

	virtual void	pop(const T& value) = 0;
	virtual bool	search(const T& value) = 0;
};