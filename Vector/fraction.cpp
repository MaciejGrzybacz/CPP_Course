
#include "fraction.h"
Fraction::Fraction(const int x, const int y) :numerator_(x), denominator_((y>0) ? y : throw std::invalid_argument("denominator_ cannot be a 0 value@")) {};

int Fraction::numerator() const noexcept {
    return Fraction::numerator_;
}

int Fraction::denominator() const noexcept {
    return Fraction::denominator_;
}

void Fraction::setNumerator(int x) noexcept {
    Fraction::numerator_=x;
}

void Fraction::setDenominator(int x) {
    if (x==0) {
        throw std::invalid_argument("denominator__ cannot be a 0 value!");
    }
    Fraction::denominator_=x;
}

Fraction Fraction::operator+(Fraction other) const {
    Fraction new_fraction;
    new_fraction.setNumerator(this->numerator()*other.denominator()+this->denominator()*other.numerator());
    new_fraction.setDenominator(this->denominator()*other.denominator());
    new_fraction.fraction_simplifier();
    return new_fraction;
}

Fraction Fraction::operator*(Fraction other) const {
    Fraction new_fraction;
    new_fraction.setNumerator(this->numerator()*other.numerator());
    new_fraction.setDenominator(this->denominator()*other.denominator());
    new_fraction.fraction_simplifier();
    return new_fraction;
}

void Fraction::fraction_simplifier() {
    int x=this->numerator();
    int y= this->denominator();
    int factor=std::gcd(abs(x), abs(y));
    this->setNumerator(x/factor);
    this->setDenominator(y/factor);
}
