#include <iostream>
#include <list>
#include <vector>
#include <string>

void	list_to_vector_transfer(const std::list<char*> &src, std::vector<std::string> &dest)
{
	dest.assign(src.cbegin(), src.cend());
}

int		main(int argc, char **argv)
{
	/* init list<char *> */
	std::list<char *> lst;
	for (int i = 0; i < argc; i++)
	{
		lst.push_back(argv[i]);
		std::cout << lst.back() << std::endl;
	}
	
	
	std::cout << "=================" << std::endl;

	/* assign list's elements to vector<string> */
	std::vector<std::string> vec = { "JUST", "FOR", " TEST " };
	list_to_vector_transfer(lst, vec);
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
	std::cout << std::endl;

	return 0;
}