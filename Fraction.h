#pragma once
class Fraction {
public:
	class ZeroDivisionException : public std::exception {};
	long long int num, den;
	Fraction(long long int, long long int);
	Fraction() : Fraction(1, 1) {};
	Fraction(long long int a) : Fraction(a, 1) {};
	friend Fraction operator+(const Fraction&, const Fraction&);
	friend Fraction operator-(const Fraction&, const Fraction&);
	friend Fraction operator*(const Fraction&, const Fraction&);
	friend Fraction operator/(const Fraction&, const Fraction&);
	Fraction& operator+=(const Fraction&);
	Fraction& operator-=(const Fraction&);
	Fraction& operator*=(const Fraction&);
	Fraction& operator/=(const Fraction&);
	friend std::ostream& operator<<(std::ostream&, Fraction const&);
	static long long int gcd(long long int, long long int);
	static long long int lcm(long long int, long long int);
};
