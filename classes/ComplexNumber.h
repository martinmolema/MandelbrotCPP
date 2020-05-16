//
// Created by martin on 28-04-20.
//

#ifndef MANDELGLADE_COMPLEXNUMBER_H
#define MANDELGLADE_COMPLEXNUMBER_H

typedef  long double complex_base_type;

class ComplexNumber {
public:
    complex_base_type real, imag;
    constexpr static complex_base_type EPSILON = (0.000003);
    constexpr static complex_base_type EPSILON_SQR = (EPSILON * EPSILON);

    ComplexNumber (complex_base_type real, complex_base_type imag);
    ComplexNumber(ComplexNumber const &other);
    complex_base_type calculateDistanceSquared(ComplexNumber other);
    ComplexNumber* sqr();
    ComplexNumber* set(complex_base_type real, complex_base_type other_imag);
    ComplexNumber* multiply(const ComplexNumber& other);
    ComplexNumber* add(const ComplexNumber& other);
    ComplexNumber* copyFrom(const ComplexNumber& other);
};


#endif //MANDELGLADE_COMPLEXNUMBER_H
