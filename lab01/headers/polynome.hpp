#pragma once

#include <list>
#include "tex_convertible.hpp"
#include "monome.hpp"

class Polynome : public TeX_convertible
{
private:
	list<Monome> container;

public:

	Polynome() {};
	Polynome(const char *str);
	Polynome(const Polynome &copy);

	

	~Polynome() {};
};
