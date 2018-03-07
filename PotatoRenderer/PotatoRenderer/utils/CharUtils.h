#ifndef _CHAR_UTILS_H_
#define _CHAR_UTILS_H_

#include <cstring>
#include <functional>

struct CharStrComparator : public std::binary_function<const char*, const char*, bool>
{
	bool operator()(const char* c1, const char* c2) const
	{
		return strcmp(c1, c2) == 0;
	}
};

struct CharStrHasher
{
	//BKDR hash algorithm
	int operator()(const char * str)const
	{
		int seed = 131;//31  131 1313 13131131313 etc//
		int hash = 0;
		while (*str)
		{
			hash = (hash * seed) + (*str);
			str++;
		}

		return hash & (0x7FFFFFFF);
	}
};

#endif // _CHAR_UTILS_H_