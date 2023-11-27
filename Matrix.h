#pragma once
class Matrix {
public:
	class IncomatibleSizeException : public std::exception {};
	std::pair<size_t, size_t> size;
	Fraction** values;
	Matrix(size_t, size_t);
	template<typename T>
	Matrix(T val, size_t m, size_t n) : size(std::make_pair(m, n)) {
		values = new Fraction * [m];
		for (size_t i = 0; i < m; ++i) {
			values[i] = new Fraction[n];
			for (size_t j = 0; j < n; ++j)
				values[i][j] = val[i][j];
		}
	}
	Matrix(const Matrix& source) : Matrix(source.values, source.size.first, source.size.second) { };
	Fraction getAdj(size_t, size_t);
	Fraction det();
	Matrix getInverse();
	friend Matrix operator+(const Matrix&, const Matrix&);
	friend Matrix operator*(const Matrix&, const Fraction&);
	friend Matrix operator*(const Fraction&, const Matrix&);
	friend Matrix operator*(const Matrix&, const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator*=(const Fraction&);
	Matrix& operator=(const Matrix&);
	Fraction* operator[](size_t idx);
	void print();
	~Matrix();
};


