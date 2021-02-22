#include "polynome.hpp"

/************************/
/*	CONSTRUCTOR & COPY	*/
/************************/

Polynome::Polynome(const char *str)
{
	std::string line(str);
	std::string tmp;

	size_t prev_pos = 0;
	size_t cur_pos = 0;
	while ((cur_pos = line.find("+", prev_pos)) < line.size() - 1)
	{
		tmp = line.substr(prev_pos, cur_pos - 1);
		container.push_back(Monome(tmp.c_str()));
		prev_pos = cur_pos + 1;
	}

	tmp = line.substr(prev_pos);
	container.push_back(Monome(tmp.c_str()));
}

Polynome::Polynome(const Polynome &copy)
{
	container = copy.container;
}


