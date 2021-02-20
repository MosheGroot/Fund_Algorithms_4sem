#include "parser.hpp"

int main(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		parse(argv[i]);
	return 0;
}
