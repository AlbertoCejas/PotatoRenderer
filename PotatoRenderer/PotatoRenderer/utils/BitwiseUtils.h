#ifndef _BITWISE_UTILS_H_
#define _BITWISE_UTILS_H_

#include <cinttypes>

namespace BitwiseUtils
{
	bool allOne(int value)
	{
		int max = ~(1 << ((sizeof(value) << 3) - 1));
		return (value == max);
	}

	bool allZero(int value)
	{
		return value == 0;
	}

	int& setNBit(int& value, int n)
	{
		value |= (1 << n);
		return value;
	}

	int& resetNBit(int& value, int n)
	{
		value &= ~(1 << n);
		return value;
	}

	bool isZero(int value, int n)
	{
		return (value & (1 << n)) == 0;
	}

	bool isSet(int value, int n)
	{
		return (value & (1 << n)) != 0;
	}

	int getFirstZeroIndex(int value)
	{
		int size = sizeof(value) << 3;

		int pos = 0;

		for (pos; pos < size && isSet(value, pos) ; pos++);

		return pos;
	}
}

#endif