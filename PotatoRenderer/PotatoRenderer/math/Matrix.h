#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <type_traits>
#include <cstring>
#include <cassert>

// COLUMN-MAJOR MEMORY LAYOUT

template <typename T, int ROW_DIM, int COL_DIM>
class Matrix
{
  public:

	static_assert(std::is_arithmetic<T>::value, "Type template must be a number");
	static_assert(ROW_DIM > 0, "Rows dimension must be greater than zero");
	static_assert(COL_DIM > 0, "Cols dimension must be greater than zero");

	Matrix()
	{
		identity();
	}

	Matrix(const Matrix& other)
	{
		setData(other.data);
	}

	inline constexpr int getRowDim() const { return ROW_DIM; }
	inline constexpr int getColDim() const { return COL_DIM; }
	inline const T* getData() const { return &data[0]; }

	T& operator()(int rowIndex, int colIndex)
	{
		assert(rowIndex > -1 && rowIndex < ROW_DIM);
		assert(colIndex > -1 && colIndex < COL_DIM);

		return data[colIndex * COL_DIM + rowIndex];
	}

	const T& operator()(int rowIndex, int colIndex) const
	{
		assert(rowIndex > -1 && rowIndex < ROW_DIM);
		assert(colIndex > -1 && colIndex < COL_DIM);

		return data[colIndex * COL_DIM + rowIndex];
	}

	constexpr unsigned int size() const { return ROW_DIM * COL_DIM; }

	void setData(const T* dataToCopy)
	{
		memcpy(data, dataToCopy, bytesSize());
	}

	Matrix& identity()
	{
		memset(data, 0, bytesSize());

		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			data[i * ROW_DIM + i] = static_cast<T>(1);
		}

		return *this;
	}

	Matrix operator+(const Matrix& other) const
	{
		Matrix result;

		unsigned int end = size() - 1;
		unsigned int halfSize = size() * 0.5f;

		for (unsigned int begin = 0u; begin < halfSize; begin++)
		{
			result.data[begin] = data[begin] + other.data[begin]; // TODO? end index
			result.data[end] = data[end] + other.data[end];
			end--;
		}

		return result;
	}

	Matrix operator-(const Matrix& other) const
	{
		Matrix result;

		for (unsigned int i = 0u; i < size(); i++)
		{
			result.data[i] = data[i] - other.data[i]; // TODO? end index
		}

		return result;
	}

	void operator+=(const Matrix& other)
	{
		for (unsigned int i = 0u; i < size(); i++)
		{
			data[i] = data[i] + other.data[i];
		}
	}

	void operator-=(const Matrix& other)
	{
		for (unsigned int i = 0u; i < size(); i++)
		{
			data[i] = data[i] - other.data[i];
		}
	}

	void print()
	{
		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			for (unsigned int j = 0u; j < COL_DIM; j++)
			{
				std::cout << data(i, j) << " ";
			}

			std::cout << "\n";
		}
	}

  private:

	constexpr unsigned int bytesSize() const { return sizeof(T) * size(); }

	T data[COL_DIM * ROW_DIM];
};

template <typename T, int ROWS_DIM, int COLS_DIM>
void operator*=(Matrix<T, ROWS_DIM, COLS_DIM>& left, const Matrix<T, ROWS_DIM, COLS_DIM>& right) // Only for same dimensions matrix
{
	for (int currentLeftRow = 0; currentLeftRow < ROWS_DIM; currentLeftRow++)
	{
		T cache[COLS_DIM];

		for (int currentRightCol = 0; currentRightCol < COLS_DIM; currentRightCol++)
		{
			T accumulator = static_cast<T>(0);

			for (int currentLeftCol = 0; currentLeftCol < COLS_DIM; currentLeftCol++)
			{
				accumulator += left(currentLeftRow, currentLeftCol) * right(currentLeftCol, currentRightCol);
			}

			cache[currentRightCol] = accumulator;
		}

		for (int i = 0; i < COLS_DIM; i++)
		{
			left(currentLeftRow, i) = cache[i];
		}
	}
}

template <typename T, int ROWS_DIM_LEFT, int COLS_DIM_LEFT, int COLS_DIM_RIGHT>
Matrix<T, ROWS_DIM_LEFT, COLS_DIM_LEFT> operator*(const Matrix<T, ROWS_DIM_LEFT, COLS_DIM_LEFT>& left, const Matrix<T, COLS_DIM_LEFT, COLS_DIM_RIGHT>& right)
{
	Matrix<T, ROWS_DIM_LEFT, COLS_DIM_LEFT> result;

	for (int currentLeftRow = 0; currentLeftRow < ROWS_DIM_LEFT; currentLeftRow++)
	{
		for (int currentRightCol = 0; currentRightCol < COLS_DIM_RIGHT; currentRightCol++)
		{
			T accumulator = static_cast<T>(0);

			for (int currentLeftCol = 0; currentLeftCol < COLS_DIM_LEFT; currentLeftCol++)
			{
				accumulator += left(currentLeftRow, currentLeftCol) * right(currentLeftCol, currentRightCol);
			}

			result(currentLeftRow, currentRightCol) = accumulator;
		}
	}

	return result;
}

using Mat3i = Matrix<int32_t, 3, 3>;
using Mat3f = Matrix<float, 3, 3>;
using Mat4i = Matrix<int32_t, 4, 4>;
using Mat4f = Matrix<float, 4, 4>;

#endif