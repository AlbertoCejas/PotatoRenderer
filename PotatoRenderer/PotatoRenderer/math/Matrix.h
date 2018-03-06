#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <type_traits>
#include <cstring>
#include <cassert>

template <typename T, int ROW_DIM, int COL_DIM>
class Matrix
{
  public:

	static_assert(std::is_arithmetic<T>::value, "Type template must be a number");
	static_assert(ROW_DIM > 0, "Rows dimension must be greater than zero");
	static_assert(COL_DIM > 0, "Cols dimension must be greater than zero");

	explicit Matrix()
	{
		memset(data, 0, sizeof(ROW_DIM * COL_DIM));
	}

	inline constexpr int32_t getRowDim() const { return ROW_DIM; }
	inline constexpr int32_t getColDim() const { return COL_DIM; }

	T* operator()(int32_t rowIndex, int32_t colIndex) const
	{
		assert(rowIndex > 0 && rowIndex < ROW_DIM);
		assert(colIndex > 0 && colIndex < COL_DIM);

		return data[rowIndex][colIndex];
	}

	void print()
	{
		for (int32_t i = 0; i < ROW_DIM; i++)
		{
			for (int32_t j = 0; j < COL_DIM; j++)
			{
				std::cout << data[i][j] << " ";
			}

			std::cout << "\n";
		}
	}

  private:

	T data[ROW_DIM][COL_DIM];
};

using Mat3i = Matrix<int32_t, 3, 3>;
using Mat3f = Matrix<float, 3, 3>;
using Mat4i = Matrix<int32_t, 4, 4>;
using Mat4f = Matrix<float, 4, 4>;

#endif