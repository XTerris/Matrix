#include <exception>
#include <iostream>

#include "Fraction.h"
#include "Matrix.h"

Matrix::Matrix(size_t m, size_t n) : size(std::make_pair(m, n)) {
	values = new Fraction * [m];
	for (size_t i = 0; i < m; ++i) {
		values[i] = new Fraction[n];
		for (size_t j = 0; j < n; ++j)
			values[i][j] = 0;
	}
}

Fraction Matrix::getAdj(size_t i, size_t j) {
	if (size.first != size.second)
		throw IncomatibleSizeException();
	Fraction** temp = new Fraction * [size.first - 1];
	for (size_t i = 0; i < size.first - 1; ++i)
		temp[i] = new Fraction[size.first - 1];
	for (size_t k = 0; k < size.first; ++k) {
		if (k == i)
			continue;
		for (size_t l = 0; l < size.second; ++l) {
			if (l == j)
				continue;
			temp[k < i ? k : k - 1][l < j ? l : l - 1] = values[k][l];
		}
	}
	Fraction res = ((j + i) % 2 ? -1 : 1) * Matrix(temp, size.first - 1, size.second - 1).det();
	for (size_t i = 0; i < size.first - 1; ++i)
		delete[] temp[i];
	delete[] temp;
	return res;
}

Fraction Matrix::det() {
	if (size.first != size.second || size.first == 0)
		throw IncomatibleSizeException();
	if (size.first == 1)
		return values[0][0];
	if (size.first == 2)
		return values[0][0] * values[1][1] - values[0][1] * values[1][0];
	Fraction res(0);
	for (size_t i = 0; i < size.first; ++i)
		res += values[i][0] * getAdj(i, 0);
	return res;
}

Matrix Matrix::getInverse() {
	if (size.first != size.second)
		throw IncomatibleSizeException();
	Fraction k = 1 / det();
	Matrix res(size.first, size.second);
	for (size_t i = 0; i < size.first; ++i)
		for (size_t j = 0; j < size.second; ++j)
			res[j][i] = getAdj(i, j);
	return res * k;
}

Matrix operator+(const Matrix& left, const Matrix& right) {
	if (left.size != right.size)
		throw Matrix::IncomatibleSizeException();
	Matrix temp(right.values, left.size.first, left.size.second);
	for (size_t i = 0; i < left.size.first; ++i)
		for (size_t j = 0; j < left.size.second; ++j)
			temp.values[i][j] += right.values[i][j];
	return temp;
}

Matrix operator*(const Matrix& mat, const Fraction& n) {
	Matrix temp = Matrix(mat.values, mat.size.first, mat.size.second);
	for (size_t i = 0; i < mat.size.first; ++i)
		for (size_t j = 0; j < mat.size.second; ++j)
			temp.values[i][j] *= n;
	return temp;
}

Matrix operator*(const Fraction& n, const Matrix& mat) {
	return mat * n;
}

Matrix operator*(const Matrix& left, const Matrix& right) {
	if (left.size.second != right.size.first)
		throw Matrix::IncomatibleSizeException();
	Matrix temp = Matrix(left.size.first, right.size.second);
	for (size_t i = 0; i < temp.size.first; ++i)
		for (size_t j = 0; j < temp.size.second; ++j)
			for (size_t k = 0; k < left.size.second; ++k)
				temp.values[i][j] += left.values[i][k] * right.values[k][j];
	return temp;
}

Matrix& Matrix::operator+=(const Matrix& right) {
	if (size != right.size)
		throw IncomatibleSizeException();
	for (size_t i = 0; i < size.first; ++i)
		for (size_t j = 0; j < size.second; ++j)
			values[i][j] += right.values[i][j];
	return *this;
}

Matrix& Matrix::operator*=(const Fraction& n) {
	for (size_t i = 0; i < size.first; ++i)
		for (size_t j = 0; j < size.second; ++j)
			values[i][j] *= n;
	return *this;
}

Matrix& Matrix::operator=(const Matrix& right) {
	size = right.size;
	for (size_t i = 0; i < size.first; ++i)
		delete[] values[i];
	delete[] values;
	values = new Fraction * [size.first];
	for (size_t i = 0; i < size.first; ++i) {
		values[i] = new Fraction[size.second];
		for (size_t j = 0; j < size.second; ++j)
			values[i][j] = right.values[i][j];
	}
	return *this;
}

Fraction* Matrix::operator[](size_t idx) {
	return this->values[idx];
}

void Matrix::print() {
	std::cout << "Size: " << size.first << " * " << size.second << std::endl;
	for (size_t i = 0; i < size.first; ++i) {
		for (size_t j = 0; j < size.second; ++j)
			std::cout << values[i][j] << " ";
		std::cout << std::endl;
	}
}

Matrix::~Matrix() {
	for (size_t i = 0; i < size.first; ++i)
		delete[] values[i];
	delete[] values;
}