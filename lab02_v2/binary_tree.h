#pragma once
/*
** ABSTRACT TREE
*/

#include "comparator.h"
#include <memory>
#include <iostream>

template<typename T>
class Binary_tree
{
protected:
	Comparator<T>*	cmp;

public:
	Binary_tree(Comparator<T>* comparator)
		: cmp(comparator)
	{}
	~Binary_tree()
	{
		delete cmp;
	}

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

	RB_node(const T& value, RB_node<T>* prev)
		: data(value), left(nullptr), right(nullptr), prev(prev), color(RED)
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
	RB_node<T>*		root;

	inline RB_node<T>*		_push_value(const T& value);
	void					_balance_check(RB_node<T>* node);
	inline void				_balance_case_1(RB_node<T>* node);
	inline void				_balance_case_2(RB_node<T>* node);
	inline void				_balance_case_3(RB_node<T>* node);

	void					_delete_process(RB_node<T>* node);
	inline void				_delete_case_rb_2(RB_node<T>* node);
	inline void				_delete_case_black_1(RB_node<T>* node);
	inline void				_delete_case_red_0(RB_node<T>* node);
	inline void				_delete_case_black_0(RB_node<T>* node);

	void					_delete_balance_process_left(RB_node<T>* brother);
	inline void				_delete_balance_case_l1__rb(RB_node<T>* node);
	inline void				_delete_balance_case_l2__rb(RB_node<T>* node);
	inline void				_delete_balance_case_l3__rb(RB_node<T>* node);
	inline void				_delete_balance_case_l4__br(RB_node<T>* node);
	inline void				_delete_balance_case_l5__bb(RB_node<T>* node);
	inline void				_delete_balance_case_l6__bb(RB_node<T>* node);

	void					_delete_balance_process_right(RB_node<T>* brother);
	inline void				_delete_balance_case_r1__rb(RB_node<T>* node);
	inline void				_delete_balance_case_r2__rb(RB_node<T>* node);
	inline void				_delete_balance_case_r3__rb(RB_node<T>* node);
	inline void				_delete_balance_case_r4__br(RB_node<T>* node);
	inline void				_delete_balance_case_r5__bb(RB_node<T>* node);
	inline void				_delete_balance_case_r6__bb(RB_node<T>* node);

	static inline unsigned char		__get_node_color(const RB_node<T>* node);
	static inline unsigned char		__get_branch(const RB_node<T>* node);
	static inline RB_node<T>*		__get_brother(const RB_node<T>* node);
	static inline void				__switch_branch(RB_node<T>* node);
	static inline size_t			__count_children(RB_node<T>* node);
	static inline RB_node<T>*		__find_min(RB_node<T>* node);
	static inline RB_node<T>*		__find_max(RB_node<T>* node);

	static void	_print_tree(std::ostream& os, const RB_node<T>* node, size_t depth);

	template<typename S>
	friend std::ostream& operator<<(std::ostream& os, const RB_tree<S>& tree);

public:
	RB_tree(Comparator<T>* comparator)
		: Binary_tree<T>(comparator)
	{
		this->root = nullptr;
	}

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
		this->root = new RB_node<T>(value, nullptr);
	else
	{
		RB_node<T>* child = _push_value(value);
		_balance_check(child);
	}
	this->root->color = BLACK;
}

template<typename T>
inline RB_node<T>* RB_tree<T>::_push_value(const T& value)
{
	RB_node<T>*		current = this->root;
	RB_node<T>*		new_child = nullptr;
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


//////	utils

template<typename T>
inline unsigned char			RB_tree<T>::__get_node_color(const RB_node<T>* node)
{
	if (!node || node->color == BLACK)
		return (BLACK);
	return (RED);
}

template<typename T>
inline unsigned char			RB_tree<T>::__get_branch(const RB_node<T>* node)
{
	if (!node->prev)
		return (ROOT);
	if (node->prev->left == node)
		return (LEFT_BRANCH);
	return(RIGHT_BRANCH);
}

template<typename T>
inline RB_node<T>*				RB_tree<T>::__get_brother(const RB_node<T>* node)
{
	unsigned char	branch = __get_branch(node);

	if (branch == ROOT)
		return (NULL);
	if (branch == LEFT_BRANCH)
		return (node->prev->right);
	return (node->prev->left);
}

template<typename T>
inline void						RB_tree<T>::__switch_branch(RB_node<T>* node)
{
	unsigned char	branch = __get_branch(node);

	if (branch == ROOT) // never should happen
		return;
	if (branch == LEFT_BRANCH)
	{
		node->prev->left = node->prev->right;
		node->prev->right = node;
	}
	else // branch == RIGHT_BRANCH
	{
		node->prev->right = node->prev->left;
		node->prev->left = node;
	}
}


////// balance part

template<typename T>
void					RB_tree<T>::_balance_check(RB_node<T>* node)
{
	if (!node || (__get_node_color(node) != __get_node_color(node->prev))) //balance is ok
		return;
	
	if (__get_node_color(node) == __get_node_color(__get_brother(node->prev)))
	{
		_balance_case_1(node);
	}
	else // uncle have black color
	{
		if (__get_branch(node) != __get_branch(node->prev))
			_balance_case_2(node);
		else
			_balance_case_3(node);
	}
}

template<typename T>
inline void				RB_tree<T>::_balance_case_1(RB_node<T>* node)
{
	node->prev->color = BLACK;					// father
	__get_brother(node->prev)->color = BLACK;	// uncle
	node->prev->prev->color = RED;				// grandfather

	_balance_check(node->prev->prev);			// recursive balance check
}

template<typename T>
inline void				RB_tree<T>::_balance_case_2(RB_node<T>* node)
{
	RB_node<T>*		next_target;

	if (__get_branch(node) == RIGHT_BRANCH)
	{
		node->prev->right = node->left;
		node->left = node->prev;
		node->prev = node->prev->prev;

		node->prev->left = node;
		node->left->prev = node;

		next_target = node->left;
	}
	else // __get_branch(node) == LEFT_BRANCH
	{
		node->prev->left = node->right;
		node->right = node->prev;
		node->prev = node->prev->prev;

		node->prev->right = node;
		node->right->prev = node;

		next_target = node->right;
	}

	_balance_case_3(next_target);
}

template<typename T>
inline void				RB_tree<T>::_balance_case_3(RB_node<T>* node)
{
	/* Colors switch */
	node->prev->color = BLACK;
	node->prev->prev->color = RED;


	/* Rotation proccess */
	RB_node<T>* tmp;
	if (__get_branch(node) == LEFT_BRANCH)
	{
		tmp = node->prev->right;
		node->prev->right = node->prev->prev;
		node->prev->prev->left = tmp;
	}
	else // __get_branch(node) == RIGHT_BRANCH
	{
		tmp = node->prev->left;
		node->prev->left = node->prev->prev;
		node->prev->prev->right = tmp;
	}


	/* Local (or global) root change */
	if (!node->prev->prev->prev) //grand grand father
		this->root = node->prev;
	else
	{
		if (__get_branch(node->prev->prev) == LEFT_BRANCH)
			node->prev->prev->prev->left = node->prev;
		else // RIGHT_BRANCH
			node->prev->prev->prev->right = node->prev;
	}
	node->prev->prev = node->prev->prev->prev;
}



////	POP section 
//////	main part

template<typename T>
void		RB_tree<T>::pop(const T& value)
{

}

////// utils

template<typename T>
static inline size_t			RB_tree<T>::__count_children(RB_node<T>* node)
{
	if (!node)
		return (-1);
	return ((node->left != nullptr) + (node->right != nullptr));
}

template<typename T>
static inline RB_node<T>*		RB_tree<T>::__find_min(RB_node<T>* node)
{
	while (node->left)
		node = node->left;
	return (node);
}

template<typename T>
static inline RB_node<T>*		RB_tree<T>::__find_max(RB_node<T>* node)
{
	while (node->right)
		node = node->right;
	return (node);
}

////// various cases

template<typename T>
void					RB_tree<T>::_delete_process(RB_node<T>* node)
{
	if (!node)
		return;

	size_t	children_count = __count_children(node);

	if (children_count == 2)
		_delete_case_rb_2(node);
	else if (children_count == 1)
		_delete_case_black_1(node); // red node can't have 1 child
	else if (node->color == RED) // children_count == 0
		_delete_case_red_0(node);
	else // node->color == BLACK
		_delete_case_black_0(node);
}

template<typename T>
inline void				RB_tree<T>::_delete_case_rb_2(RB_node<T>* node)	// red or black node with 2 children
{
	RB_node<T>*		to_swap_node = __find_min(node->right);

	std::swap(node->data, to_swap_node->data);
	_delete_process(to_swap_node);
}

template<typename T>
inline void				RB_tree<T>::_delete_case_black_1(RB_node<T>* node) // black node with 1 child
{
	if (node->left)
	{
		std::swap(node->data, node->left->data);
		_delete_process(node->left);
	}
	else // node->right ||| (node->right != nullptr) guaranteed
	{
		std::swap(node->data, node->right->data);
		_delete_process(node->right);
	}
}

template<typename T>
inline void				RB_tree<T>::_delete_case_red_0(RB_node<T>* node) // red node with 0 children
{
	if (__get_branch(node) == LEFT_BRANCH)
		node->prev->left = nullptr;
	else // __get_branch(node) == RIGHT_BRANCH
		node->prev->right = nullptr;
	delete node;
}

template<typename T>
inline void				RB_tree<T>::_delete_case_black_0(RB_node<T>* node) // black node with 0 children
{
	RB_node<T>*		balance_target = __get_brother(node);
	unsigned char	branch = __get_branch(node);

	if (branch == LEFT_BRANCH)
		node->prev->left = nullptr;
	else if (branch == RIGHT_BRANCH)
		node->prev->right = nullptr;
	else // branch == ROOT
		this->root = nullptr;
	delete node;

	// black height was changed! Need to balance...
	_delete_balance_process(balance_target);
}

///// balance after case_black_0 delete

template<typename T>
void					RB_tree<T>::_delete_balance_process_left(RB_node<T>* node)
{
	if (!node)
		return;

	if (brother->prev.color == RED)
	{
		// (brother.color == BLACK) guaranteed by the rules
		if (__get_node_color(brother->left) == RED)
			_delete_balance_case_2__rb(brother);
		else if (__get_node_color(brother->right) == BLACK) // brother->left.color = BLACK too
			_delete_balance_case_1__rb(brother);
		// else there is no need to balance
	}
	else // brother->prev.color == BLACK
	{
		if (brother->color == RED)
		{
			// brother->left.color == BLACK

		}
	}
}

template<typename T>
inline void				RB_tree<T>::_delete_balance_case_l1__rb(RB_node<T>* node);

template<typename T>
inline void				RB_tree<T>::_delete_balance_case_l2__rb(RB_node<T>* node);

template<typename T>
inline void				RB_tree<T>::_delete_balance_case_l3__rb(RB_node<T>* node);

template<typename T>
inline void				RB_tree<T>::_delete_balance_case_l4__br(RB_node<T>* node);

template<typename T>
inline void				RB_tree<T>::_delete_balance_case_l5__bb(RB_node<T>* node);

template<typename T>
inline void				RB_tree<T>::_delete_balance_case_l6__bb(RB_node<T>* node);

////	SEARCH section 

template<typename T>
bool			RB_tree<T>::search(const T& value)
{
	RB_node<T>*		current = this->root;
	int				cmp_result;

	while (current)
	{
		cmp_result = this->cmp->compare(value, current->data);
		if (cmp_result < 0)
			current = current->left;
		else if (cmp_result > 0)
			current = current->right;
		else
			return (true);
	}
	return (false);
}

////	COUT overload section
template<typename T>
std::ostream& operator<<(std::ostream& os, const RB_tree<T>& tree)
{
	RB_tree<T>::_print_tree(os, tree.root, 0);
	return (os);
}

template<typename T>
void					RB_tree<T>::_print_tree(std::ostream& os, const RB_node<T>* node, size_t depth)
{
	for (size_t i = 0; i < depth; i++)
		os << "  ";

	if (!node)
	{
		os << "\x1b[40;37m[ null ]\x1b[m" << std::endl;
		return;
	}
	else if (node->color == BLACK)
		os << "\x1b[40;37m[  " << node->data << "  ]\x1b[m" << std::endl;
	else
		os << "\x1b[41;37m[  " << node->data << "  ]\x1b[m" << std::endl;

	_print_tree(os, node->left, depth + 1);
	_print_tree(os, node->right, depth + 1);
}
