#include <iostream>

using namespace std;

template<typename T, int N, int M>

class Matrix {

private:

	T matrix[N][M];

public:
	// ������� ����������� - ����������� ������� ���������� ��� �������� ������ ������
	Matrix() {}

	// ����������� ����������� (������� �������� ��������)
	Matrix(const Matrix<T, N, M>& other) 
	{
		for (int i = 0; i < N; ++i) 
		{
			for (int j = 0; j < M; ++j) 
			{
				matrix[i][j] = other.matrix[i][j];
			}
		}
	}

	// �������� ������������ ������������ (�������� ��� ������������ �������)
	Matrix<T, N, M>& operator=(const Matrix<T, N, M>& other) 
	{
		if (this != &other) 
		{
			for (int i = 0; i < N; ++i) 
			{
				for (int j = 0; j < M; ++j) 
				{
					matrix[i][j] = other.matrix[i][j];
				}
			}
		}
		return *this;
	}

	//�������� �����
	friend std::istream& operator>>(std::istream& in, Matrix<T, N, M>& m) 
	{
		for (int i = 0; i < N; ++i) 
		{
			for (int j = 0; j < M; ++j)
			{
				in >> m.matrix[i][j]; // �������� ����� � �������� ������
			}
		}
		return in;
	}

	//�������� ������
	friend std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& m) 
	{
		for (int i = 0; i < N; ++i) 
		{
			for (int j = 0; j < M; ++j) 
			{
				out << m.matrix[i][j] << " "; // ��������� ����� �� ��������� �������
			}
			out << std::endl;
		}
		return out;
	}

	// �������� (+)
	Matrix<T, N, M> operator+(const Matrix<T, N, M>& other) const 
	{
		Matrix<T, N, M> result;
		for (int i = 0; i < N; ++i) 
		{
			for (int j = 0; j < M; ++j) 
			{
				result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
			}
		}
		return result;
	}

	// �������� (+=)
	Matrix<T, N, M>& operator+=(const Matrix<T, N, M>& other) 
	{
		for (int i = 0; i < N; ++i) 
		{
			for (int j = 0; j < M; ++j) 
			{
				matrix[i][j] += other.matrix[i][j];
			}
		}
		return *this;
	}

	// �������� (*)
	template<int K>
	Matrix<T, N, K> operator*(const Matrix<T, M, K>& other) const 
	{
		Matrix<T, N, K> result;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < K; ++j) 
			{
				int C = 0;
				for (int k = 0; k < M; ++k) 
				{
					C = C + (matrix[i][k] * other.matrix[k][j]);
					result.matrix[i][j] = C;
				}
			}
		}
		return result;
	}

	// �������� (*=)
	Matrix<T, N, M>& operator*=(const Matrix<T, N, M>& other) {
		*this = *this * other;
		return *this;
	}

	// �������� (++)
	Matrix<T, N, M>& operator++() 
	{
		for (int i = 0; i < N; ++i) 
		{
			for (int j = 0; j < M; ++j) 
			{
				++matrix[i][j];
			}
		}
		return *this;
	}


	// ���������� ������������
	T determinant() const 
	{
		if (N == 1) 
		{
			return matrix[0][0];
		}
		if (N == 2) 
		{
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		if (N == 3) 
		{
			return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
				matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
				matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
		}
	}

	// �������� ��� ��������� ��������
	T& operator()(int i, int j) 
	{
		return matrix[i - 1][j - 1];
	}

	// �������� ��� ��������� ��������
	const T& operator()(int i, int j) const 
	{
		return matrix[i - 1][j - 1];
	}

};

int main() {

	Matrix<int, 3, 3> m1, m2, m3;

	std::cout << "Enter the first matrix:" << std::endl;
	std::cin >> m1;
	std::cout << "Enter the second matrix:" << std::endl;
	std::cin >> m2;

	std::cout << "m1 + m2:" << std::endl;
	m3 = m1 + m2;
	std::cout << m3;

	std::cout << "m1 += m2:" << std::endl;
	m1 += m2;
	std::cout << m1;

	std::cout << "m1 * m2:" << std::endl;
	m3 = m1 * m2;
	std::cout << m3;

	std::cout << "m1 *= m2:" << std::endl;
	m1 *= m2;
	std::cout << m1;

	std::cout << "++m1:" << std::endl;
	++m1;
	std::cout << m1;

	std::cout << "determinant of m1: " << m1.determinant() << std::endl;

	std::cout << "m1(2, 2): " << m1(2, 2) << std::endl;

	std::cout << "m1(2, 2) = 999" << std::endl;
	m1(2, 2) = 999;

	std::cout << m1;

	return 0;

}