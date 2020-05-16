//
// Created by martin on 29-04-20.
//

#include "Dimension.h"
#include "Rectangle.h"
#include <stdlib.h>
Dimension::Dimension(double w, double h) : w(w), h(h) {}

Dimension::Dimension(double x1, double y1, double x2, double y2) {
    this->w = abs( y2 - y1 );
    this->h = abs( x2 - x1 );
}

double Dimension::getW() const {
    return w;
}

double Dimension::getH() const {
    return h;
}

Dimension::Dimension(Rectangle r) {
    this->w = r.width();
    this->h = r.height();
}

double Dimension::area_size() const {
    return this->w * this->h;
}
