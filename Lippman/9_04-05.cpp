#include <vector>

/* Exercise 9.4 
** Search element in vector<int> between <begin> and <end> iterators.
** Returns True or False.
*/
bool bool_search(std::vector<int>::iterator begin,
					std::vector<int>::iterator end,
					int to_find)
{
	while (begin < end)
	{
		if (*begin == to_find)
			return true;
		begin++;
	}
	return false;
}

/* Exercise 9.5 
** Search element in vector<int> between <begin> and <end> iterators.
** If element does not exist -- functions returns .end() iterator.
*/
std::vector<int>::iterator it_search(std::vector<int>::iterator begin,
										std::vector<int>::iterator end,
										int to_find)
{
	while (begin < end)
	{
		if (*begin == to_find)
			break;
		begin++;
	}
	return begin;
}
