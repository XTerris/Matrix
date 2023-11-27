#pragma once
#include <iostream>
#include <vector>

#include "Fraction.h"
#include "Matrix.h"

const int N = 4, M = 4;

int main() {
	std::vector<std::vector<Fraction>> arr(3, std::vector<Fraction>(3, Fraction(3)));
	Fraction** a = new Fraction * [3];
	a[0] = new Fraction[3]{ 1, 2, 3 };
	a[1] = new Fraction[3]{ 4, 3, 3 };
	a[2] = new Fraction[3]{ 7, 8, 9 };
	arr[2][1] = 5;
	arr[0][1] = 4;
	arr[1][2] = 8;
	Matrix mat(arr, 3, 3), mat2(a, 3, 3);
	Matrix inv = mat.getInverse(), inv2 = mat2.getInverse();
	mat.print();
	inv.print();
	mat2.print();
	inv2.print();
	return 0;
}
