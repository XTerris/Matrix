#include <exception>
#include <iostream>

#include "Fraction.h"


Fraction::Fraction(long long int a, long long int b) {
	if (b == 0)
		throw ZeroDivisionException();
	if (a == 0) {
		num = 0;
		den = 1;
	}
	else {
		num = abs(a) / Fraction::gcd(abs(a), abs(b));
		den = abs(b) / Fraction::gcd(abs(a), abs(b));
		if (a * b < 0)
			num = -num;
	}
};

Fraction operator+(const Fraction& left, const Fraction& right) {
	long long int new_den = Fraction::lcm(left.den, right.den);
	return Fraction(left.num * (new_den / left.den) + right.num * (new_den / right.den), new_den);
};

Fraction operator-(const Fraction& left, const Fraction& right) {
	long long int new_den = Fraction::lcm(left.den, right.den);
	return Fraction(left.num * (new_den / left.den) - right.num * (new_den / right.den), new_den);
};

Fraction operator*(const Fraction& left, const Fraction& right) {
	return Fraction(left.num * right.num, left.den * right.den);
};

Fraction operator/(const Fraction& left, const Fraction& right) {
	return Fraction(left.num * right.den, left.den * right.num);
};

Fraction& Fraction::operator+=(const Fraction& right) {
	*this = *this + right;
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& right) {
	*this = *this - right;
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& right) {
	*this = *this * right;
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& right) {
	*this = *this / right;
	return *this;
}

std::ostream& operator<<(std::ostream& s, Fraction const& frac) {
	s << frac.num << "/" << frac.den;
	return s;
}

long long int Fraction::gcd(long long int a, long long int b) {
	return b ? gcd(b, a % b) : a;
};

long long Fraction::lcm(long long int a, long long int b) {
	return abs(a * b) / gcd(a, b);
};