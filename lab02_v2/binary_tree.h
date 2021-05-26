#pragma once
/*
** ABSTRACT TREE
*/

#include "comparator.h"
#include <memory>

template<typename T>
class Binary_tree
{
protected:
	std::shared_ptr<Comparator<T>>	cmp;

public:
	Binary_tree(const std::shared_ptr<Comparator<T>>& comparator)
		: cmp(comparator)
	{}
	~Binary_tree() {}

	virtual void	push(const T& value) = 0;
	virtual void	pop(const T& value) = 0;
	virtual bool	search(const T& value) = 0;
};



/*
** RB_TREE
*/
template<typename T> class RB_tree; //forward declaring

// RB_tree_node
# define BLACK 0
# define RED 1

template<typename T>
class RB_node
{
private:
	template<typename S>
	friend class RB_tree;

	T					data;
	unsigned char		color;

	RB_node<T>*			left;
	RB_node<T>*			right;
	RB_node<T>*			prev;

	RB_node(const T& value, const RB_node<T>* prev)
		: data(value), left(nullptr), right(nullptr), prev(nullptr), color(RED)
	{}

	~RB_node()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}
};

// RB_tree

# define ROOT			0
# define LEFT_BRANCH	1
# define RIGHT_BRANCH	2

template<typename T>
class RB_tree : public Binary_tree<T>
{
private:
	RB_node<T>*		root = nullptr;

	inline RB_node<T>*	_push_value(const T& value);
	inline void			_balance_check(RB_node<T>* node);
	
	unsigned char		_get_node_color(const RB_node<T>* node);
	unsigned char		_get_branch(const RB_node<T>* node);
	RB_node<T>*			_get_brother(const RB_node<T>* node);

public:
	~RB_tree()
	{
		if (this->root)
			delete root;
	}

	virtual void	push(const T& value) override;
	virtual void	pop(const T& value) override;
	virtual bool	search(const T& value) override;
};

////	PUSH section 
//////	main part

template<typename T>
void		RB_tree<T>::push(const T& value)
{
	if (!this->root)
	{
		this->root = new RB_node<T>(value, nullptr);
		this->root->color = BLACK;
		return;
	}

	RB_node<T>* child = _push_value(value);
	_balance_check(child);
}

template<typename T>
inline RB_node<T>* RB_tree<T>::_push_value(const T& value)
{
	RB_node<T>*		current = this->root;
	RB_node<T>*		new_child;
	int				cmp_result;

	while (true)
	{
		cmp_result = this->cmp->compare(value, current->data);
		if (cmp_result < 0)
		{
			if (!current->left)
			{
				current->left = new RB_node<T>(value, current);
				new_child = current->left;
				break;
			}
			else
				current = current->left;
		}
		else if (cmp_result > 0)
		{
			if (!current->right)
			{
				current->right = new RB_node<T>(value, current);
				new_child = current->right;
				break;
			}
			else
				current = current->right;
		}
		else
			break;
	}
	return (new_child);
}

//////	balance part

template<typename T>
unsigned char			RB_tree<T>::_get_node_color(const RB_node<T>* node)
{
	if (!node || node->color == BLACK)
		return (BLACK);
	return (RED);
}

template<typename T>
unsigned char			RB_tree<T>::_get_branch(const RB_node<T>* node)
{
	if ()
}

template<typename T>
RB_node<T>*				RB_tree<T>::_get_brother(const RB_node<T>* node)
{
	
}