#include <iostream>
#include <stdexcept> // std::out_of_range
#include <numeric>   // std::gcd

#include "fraction.h"

Fraction::Fraction(const int& numerator,const int& denominator)
	:numerator_(numerator),
	denominator_(denominator){
	if (denominator == 0) {
		throw std::invalid_argument("denominator cannot be zero");
	}
}


int Fraction::numerator() const {
	return numerator_;
}

void Fraction::setNumerator(int numerator) {
	numerator_ = numerator;
}

int Fraction::denominator() const {
	return denominator_;
}

void Fraction::setDenominator(int denominator) {
	if (denominator == 0) {
		throw std::invalid_argument("denominator cannot be zero");
	}
	denominator_ = denominator;
}

Fraction Fraction::operator+(const Fraction &other) const {

	int nww = std::lcm(denominator(), other.denominator());
	int thisMult = nww/denominator();
	int otherMult = nww/other.denominator();

	Fraction res = Fraction();
	res.setNumerator((this->numerator()*thisMult)+(other.numerator()*otherMult));
	res.setDenominator(nww);

	int nwd = std::gcd(res.numerator(), res.denominator());
	if (nwd > 1) {
		res.setNumerator(res.numerator()/nwd);
		res.setDenominator(res.denominator()/nwd);
	}

	return res;
}

Fraction Fraction::operator*(const Fraction &other) const {
	Fraction res = Fraction();
	res.setNumerator(this->numerator()*other.numerator());
	res.setDenominator(this->denominator()*other.denominator());

	int nwd = std::gcd(res.numerator(), res.denominator());
	if (nwd > 1) {
		res.setNumerator(res.numerator()/nwd);
		res.setDenominator(res.denominator()/nwd);
	}

	return res;
}
