#include <vector>
#include <list>

/* Exercise 9.15
** Compare two vectors of integers.
** Returns True or False.
*/
bool vector_equals(const std::vector<int>& a, const std::vector<int>& b)
{
	if (a.size() != b.size())
		return false;

	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;

	return true;
}

/* Exercise 9.16
** Compare list and vector with integers.
** Returns True or False.
*/
bool vector_equals(const std::list<int>& a, const std::vector<int>& b)
{
	if (a.size() != b.size())
		return false;

	std::list<int>::const_iterator it1 = a.cbegin();
	std::vector<int>::const_iterator it2 = b.cbegin();
	for ( ; it1 != a.cend(); it1++, it2++)
		if (*it1 != *it2)
			return false;

	return true;
}