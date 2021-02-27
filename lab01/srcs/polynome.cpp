#include "nomes.hpp"

/************************/
/*		  UTILS		    */
/************************/

void Polynome::compress_polynome()
{
	container.sort(compare_ascending);

	std::list<Monome> tmp;
	for (const auto& mon : container)
	{
		if (tmp.empty() && mon.coeff)
			tmp.push_back(mon);
		else if (compare_vars(tmp.back(), mon))
			tmp.back().coeff += mon.coeff;
		else if (mon.coeff)
			tmp.push_back(mon);
	}
	tmp.remove_if([](const Monome& m){ return m.coeff == 0; });

	container = tmp;
}

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
		tmp = line.substr(prev_pos, cur_pos - prev_pos);
		container.push_back(Monome(tmp.c_str()));
		prev_pos = cur_pos + 1;
	}

	tmp = line.substr(prev_pos, line.size() - prev_pos);
	container.push_back(Monome(tmp.c_str()));

	compress_polynome();
}

Polynome::Polynome(const Polynome &copy)
{
	container = copy.container;
}

Polynome::Polynome(const Monome &monome)
{
	container.push_back(monome);
}

/************************/
/*		OPERATOR=		*/
/************************/

Polynome& Polynome::operator=(const Polynome &m)
{
	container = m.container;
	return (*this);
}

Polynome& Polynome::operator=(const char *str)
{
	Polynome tmp(str);
	container = tmp.container;
	return (*this);
}

Polynome& Polynome::operator=(const Monome &m)
{
	container.clear();
	container.push_back(m);
	return (*this);
}

/************************/
/*	   OPERATOR+=,+		*/
/************************/

Polynome& Polynome::operator+=(const Polynome &m)
{
	std::list<Monome> tmp(m.container);
	container.merge(tmp, compare_ascending);
	compress_polynome();
	return (*this);
}

Polynome Polynome::operator+(const Polynome &m) const
{
	Polynome tmp(*this);
	tmp += m;
	return tmp;
}

/************************/
/*	   OPERATOR-=,-		*/
/************************/

Polynome& Polynome::operator-=(const Polynome &m)
{
	std::list<Monome> tmp_list = m.container;
	for (auto& elem : tmp_list)
		elem.coeff *= -1;

	container.merge(tmp_list, compare_ascending);
	compress_polynome();
	return (*this);
}

Polynome Polynome::operator-(const Polynome &m) const
{
	Polynome tmp(*this);
	tmp -= m;
	return tmp;
}

/************************/
/*	   OPERATOR*=,*		*/
/************************/

Polynome& Polynome::operator*=(const Polynome &m)
{
	std::list<Monome> tmp_list;
	
	for (const auto& elem_1 : container)
		for (const auto& elem_2 : m.container)
			tmp_list.push_back(elem_1 * elem_2);

	container = tmp_list;
	compress_polynome();
	
	return (*this);
}

Polynome Polynome::operator*(const Polynome &m) const
{
	Polynome tmp(*this);
	tmp *= m;
	return (tmp);
}

/************************/
/*	   OPERATOR/=,/		*/
/************************/

Polynome& Polynome::operator/=(const char var)
{
	for (auto& mon : container)
		mon /= var;

	compress_polynome();
	return (*this);
}

Polynome Polynome::operator/(const char var) const
{
	Polynome tmp(*this);
	tmp /= var;
	return (tmp);
}

Polynome& Polynome::operator/=(const char *vars)
{
	size_t i;
	for (auto& mon : container)
		for (i = 0; vars[i]; i++)
			mon /= vars[i];

	compress_polynome();
	return (*this);
}

Polynome Polynome::operator/(const char *vars) const
{
	Polynome tmp(*this);
	tmp /= vars;
	return (tmp);
}

/************************/
/*	  OPERATOR==,!=		*/
/************************/

bool Polynome::operator==(const Polynome &m) const
{
	std::list<Monome>::const_iterator it1, it2;
	for (it1 = container.begin(), it2 = m.container.begin();
			it1 != container.end() && it2 != m.container.end();
			it1++, it2++)
		if ((*it1) != (*it2))
			return false;

	return true;
}

bool Polynome::operator!=(const Polynome &m) const
{
	return (!(*this == m));
}

/************************/
/*	  OPERATOR<<,>>		*/
/************************/

std::ostream& operator<<(std::ostream &os, const Polynome &m)
{
	if (m.container.empty())
	{
		os << 0;
		return os;
	}

	std::list<Monome>::const_iterator it = m.container.begin();
	os << *it; ++it;
	for ( ; it != m.container.end(); ++it)
		os << " + " << *it;

	return os;
}

std::istream& operator>>(std::istream &is, Polynome &m)
{
	std::string tmp;
	std::getline(is, tmp);
	
	Polynome m_tmp(tmp.c_str());
	m = m_tmp;

	return is;
}

/************************/
/*	 FRIEND METHODS		*/
/************************/

bool is_homogenous_polynome(const Polynome &m)
{
	if (m.container.empty())
		return true;

	unsigned int gen_degree = m.container.front().general_degree();
	for (const auto& mon : m.container)
		if (mon.general_degree() != gen_degree)
			return false;

	return true;
}

bool is_harmonic_polynome(const Polynome &m)
{
	std::map<char, bool> all_vars;
	for (const auto& mon: m.container)
		for (const auto& [key, value] : mon.vars)
			all_vars[key] = true;

	Polynome tmp;
	for (const auto& [key, value] : all_vars)
	{
		tmp = m / key;
		tmp /= key;
		if (!tmp.container.empty())
			return false;
	}

	return (true);
}

/************************/
/*	 	 CONVERT		*/
/************************/

std::string Polynome::convert() const
{
	if (container.empty())
		return "0";

	std::list<Monome>::const_iterator it = container.begin();

	std::string out = it->convert(); it++;
	for ( ; it != container.end(); it++)
		out += " + " + it->convert();

	return (out);
}
