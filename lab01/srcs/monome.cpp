#include "monome.hpp"

/************************/
/*	CONSTRUCTOR	& COPY	*/
/************************/

Monome::Monome(const char *str)
	: Monome(Monome())
{
	if (!str)
		return;
	
	coeff = std::stoi(str);
	while (*str)
	{
		while (isdigit(*str))
			str++;
		if (!*str)
			break;
		
		vars[*str] = std::atoi(str + 1);
		str++;
	}
}

Monome::Monome(const Monome &copy)
{
	coeff = copy.coeff;
	vars = copy.vars;
}

/************************/
/*		OPERATOR=		*/
/************************/

Monome& Monome::operator=(const Monome &m)
{
	coeff = m.coeff;
	vars = m.vars;
	return (*this);
}

Monome& Monome::operator=(const char *str)
{
	Monome tmp(str);
	*this = tmp;
	return (*this);
}

/************************/
/*	   OPERATOR+=,+	    */
/************************/

Monome& Monome::operator+=(const Monome &m)
{
	for (const auto& [key, value] : m.vars)
		if (!vars.contains(key))
			throw std::invalid_argument("Monomes are not equal! "
										"Can't plus them.");
	coeff += m.coeff;
	return (*this);
}

Monome Monome::operator+(const Monome &m) const
{
	Monome tmp(*this);
	tmp += m;
	return tmp;
}

/************************/
/*	   OPERATOR-=,-	    */
/************************/

Monome& Monome::operator-=(const Monome &m)
{
	for (const auto& [key, value] : m.vars)
		if (!vars.contains(key))
			throw std::invalid_argument("Monomes are not equal! "
										"Can't minus them.");
	coeff -= m.coeff;
	return (*this);
}

Monome Monome::operator-(const Monome &m) const
{
	Monome tmp(*this);
	tmp -= m;
	return tmp;
}

/************************/
/*	   OPERATOR*=,*	    */
/************************/

Monome& Monome::operator*=(const Monome &m)
{
	for (const auto& [key, value] : m.vars)
		if (!vars.contains(key))
			vars[key] = value;
		else
			vars[key] += value;

	coeff += m.coeff;
	return (*this);
}

Monome Monome::operator*(const Monome &m) const
{
	Monome tmp(*this);
	tmp *= m;
	return tmp;
}

/************************/
/*	   OPERATOR*=,*	    */
/************************/

Monome& Monome::operator/=(const char var)
{
	if (!vars.contains(var) || vars[var] == 0)
		coeff = 0;
	else
		coeff *= vars[var]--;

	return (*this);
}

Monome Monome::operator/(const char var) const
{
	Monome tmp(*this);
	tmp /= var;
	return tmp;
}

/************************/
/*	  OPERATOR==,!=     */
/************************/

bool Monome::operator==(const Monome &m) const
{
	if (coeff != m.coeff)
		return false;

	for (const auto& [key, value] : m.vars)
		if (!vars.contains(key))
		{
			if (value != 0)
				return false;
		}
		else if (vars.at(key) != value)
			return false;
	
	return true;
}

bool Monome::operator!=(const Monome &m) const
{
	return (!(*this == m));
}

/************************/
/*	  OPERATOR<<,>>     */
/************************/

std::ostream& operator<<(std::ostream& os, const Monome &m)
{
	os << m.coeff;
	for (const auto& [key, value] : m.vars)
		os << key << "^" << value;
	return os;
}

std::istream& operator>>(std::istream& is, Monome &m)
{
	std::string tmp;
	is >> tmp;
	m = Monome(tmp.c_str());
	return is;
}

/************************/
/*	  	  CONVERT       */
/************************/

std::string Monome::convert() const
{
	std::string out;

	out = std::to_string(coeff);
	for (const auto& [key, value] : vars)
	{
		out.push_back(key);
		out += "^{" + std::to_string(value) + "}";
	}
	return (out);
}
