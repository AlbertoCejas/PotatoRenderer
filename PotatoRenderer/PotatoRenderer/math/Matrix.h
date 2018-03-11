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
		identity();
	}

	Matrix(const Matrix& other)
	{
		setData(other.data);
	}

	inline constexpr int getRowDim() const { return ROW_DIM; }
	inline constexpr int getColDim() const { return COL_DIM; }
	inline const T* getData() const { return &data[0][0]; }

	T* operator[](size_t index)
	{
		assert(index < ROW_DIM);
		return data[index];
	}

	const T* const operator[](size_t index) const
	{
		assert(index < ROW_DIM);
		return data[index];
	}

	T* operator()(int rowIndex, int colIndex) const
	{
		assert(rowIndex > 0 && rowIndex < ROW_DIM);
		assert(colIndex > 0 && colIndex < COL_DIM);

		return &data[rowIndex][colIndex];
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
			data[i][i] = static_cast<T>(1);
		}

		return *this;
	}

	Matrix operator+(const Matrix& other) const 
	{
		Matrix result;
		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			for (unsigned int j = 0u; j < COL_DIM; j++)
			{
				result.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return result;
	}

	Matrix operator*(const Matrix& other) const
	{
		Matrix result;
		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			for (unsigned int j = 0u; j < COL_DIM; j++)
			{
				result.data[i][j] = data[i][j] * other.data[i][j];
			}
		}
		return result;
	}

	Matrix operator-(const Matrix& other) const
	{
		Matrix result;
		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			for (unsigned int j = 0u; j < COL_DIM; j++)
			{
				result.data[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return result;
	}

	void operator+=(const Matrix& other)
	{
		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			for (unsigned int j = 0u; j < COL_DIM; j++)
			{
				data[i][j] = data[i][j] + other.data[i][j];
			}
		}
	}

	void operator*=(const Matrix& other)
	{
		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			for (unsigned int j = 0u; j < COL_DIM; j++)
			{
				data[i][j] = data[i][j] * other.data[i][j];
			}
		}
	}

	void operator-=(const Matrix& other)
	{
		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			for (unsigned int j = 0u; j < COL_DIM; j++)
			{
				data[i][j] = data[i][j] - other.data[i][j];
			}
		}
	}

	void print()
	{
		for (unsigned int i = 0u; i < ROW_DIM; i++)
		{
			for (unsigned int j = 0u; j < COL_DIM; j++)
			{
				std::cout << data[i,j] << " ";
			}

			std::cout << "\n";
		}
	}

  private:

	constexpr unsigned int bytesSize() const { return sizeof(T) * size(); }

	T data[ROW_DIM][COL_DIM];
};

using Mat3i = Matrix<int32_t, 3, 3>;
using Mat3f = Matrix<float, 3, 3>;
using Mat4i = Matrix<int32_t, 4, 4>;
using Mat4f = Matrix<float, 4, 4>;

#endif