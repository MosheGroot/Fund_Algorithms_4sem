#include "binary_tree.h"

void	push_test(RB_tree<int>& tree)
{
	tree.push(10);
	tree.push(15);
	tree.push(20);
	//tree.push(25);
	//tree.push(0);
	//tree.push(12);
	//tree.push(17);
	//tree.push(50);
	//tree.push(40);
	//tree.push(5);
	//tree.push(3);
	//tree.push(100);
	//tree.push(150);
	//tree.push(125);

	std::cout << tree << std::endl;
}

int main()
{
	RB_tree<int>	tree(new Ascending_comparator<int>);

	push_test(tree);

}