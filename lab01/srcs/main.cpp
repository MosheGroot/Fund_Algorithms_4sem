#include "parser.hpp"
#include <cstdlib>

int main(int argc, char **argv)
{
	std::string tex_file;
	for (int i = 1; i < argc; i++)
	{
		tex_file = parse(argv[i]);
	//	if (!tex_file.empty())
	//		std::system(("pdftex " + tex_file).c_str());
	}

	return 0;
}
