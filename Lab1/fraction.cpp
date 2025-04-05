#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

#include "fraction.h"

Fraction::Fraction() {
    numerator_ = 0;
    denominator_ = 1;
}

Fraction::Fraction(int numerator, int denominator = 1) {
    numerator_ = numerator;
    denominator_ = denominator;
}

int Fraction::numerator() const {

    return numerator_;

}

void Fraction::setNumerator(int x) {

    numerator_ = x;

}

int Fraction::denominator() const {

    return denominator_;

}
void Fraction::setDenominator(int y) {

    denominator_ = y;

}

void Fraction::print() const {

    cout << numerator_ << "/" << denominator_ << "\n";

}

int Fraction::removedFractions_=0;

int Fraction::removedFractions() {

    return removedFractions_;

}

Fraction::~Fraction() {

    removedFractions_++;

}

void Fraction::save(std::ostream& os) const {

    os << numerator_ << "/" << denominator_;

}
void Fraction::load(std::istream& is) {

    string string;
    is >> string;
    numerator_ = stoi(string.substr(0, string.find('/')));
    denominator_ = stoi(string.substr(string.find('/') + 1));

}

int Fraction::invalidDenominatorValue() {
    return invalidDenominatorValue_;
}


const string Fraction::fractionName() const {

    return fractionName_;

}

Fraction::Fraction(int a, int b, const std::string & name): numerator_(a),
                                                            denominator_(b),
                                                            fractionName_(name) {}


