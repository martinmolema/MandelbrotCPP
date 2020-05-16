//
// Created by martin on 28-04-20.
//

#include "ComplexNumber.h"


ComplexNumber::ComplexNumber(complex_base_type real, complex_base_type imag) {
    set(real, imag);
}// constructor

ComplexNumber::ComplexNumber(ComplexNumber const &other) {
    this->real = other.real;
    this->imag = other.imag;
}// constructor

ComplexNumber *ComplexNumber::set(complex_base_type real, complex_base_type other_imag) {
    this->real = real;
    this->imag = other_imag;

    return this;
}// set

ComplexNumber *ComplexNumber::multiply(const ComplexNumber &other) {

    complex_base_type newReal = (this->real * other.real - this->imag * other.imag);
    complex_base_type newimag = (this->real * other.imag + this->imag * other.real);

    this->set(newReal, newimag);

    return this;
}//multiply

ComplexNumber *ComplexNumber::sqr() {
    this->multiply(*this);
}

ComplexNumber *ComplexNumber::add(const ComplexNumber &other) {
    this->set(this->real + other.real, this->imag + other.imag);

    return this;
}// add

ComplexNumber *ComplexNumber::copyFrom(const ComplexNumber &other) {
    this->set(other.real, other.imag);

    return this;
}

complex_base_type ComplexNumber::calculateDistanceSquared(ComplexNumber other) {
    complex_base_type p1 = this->real - other.real;
    complex_base_type p2 = this->imag - other.imag;
    return (p1 * p1 + p2 * p2);
}