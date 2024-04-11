
#include <iostream>
#include <cstring>
#include <cctype>
#include "fraction.h"

int Fraction::removedFractions_ = 0;

Fraction::Fraction() : numerator_(0), denominator_(1) { };

Fraction::Fraction(int n, const int d) : numerator_(n), denominator_(d) { };

Fraction::Fraction(int n, int d, std::string name) : numerator_(n), denominator_(d), fractionName_(std::move(name)) { };

int Fraction::getNumerator() const { return numerator_; };

int Fraction::getDenominator() const { return denominator_; };

std::string Fraction::getFractionName() const { return fractionName_; };

int Fraction::getInvalidDenominatorValue() { return invalidDenominatorValue; };

int Fraction::getDefaultDenominatorValue() { return defaultDenominatorValue; };

void Fraction::setNumerator(int n) { numerator_ = n; };

void Fraction::setDenominator(int d) { denominator_ = d; };

void Fraction::print() const { std::cout << numerator_ << "/" << denominator_<<std::endl; };

int Fraction::removedFractions() { return removedFractions_; };

void Fraction::load(std::istream& is) {
    std::string line;
    getline(is, line);
    int i = 0;
    numerator_ = 0;
    denominator_ = 0;
    while (line[i] != '/') {
        numerator_ = numerator_ * 10 + (line[i] - '0');
        i++;
    }
    i++;
    while (i < line.length()) {
        denominator_ = denominator_ * 10 + (line[i] - '0');
        i++;
    }
}

void Fraction::save(std::ostream& os) const { os << numerator_ << "/" << denominator_; };

Fraction::~Fraction() { removedFractions_++; };

