//
// Created by martin on 29-04-20.
//

#include "RGBColor.h"

RGBColor::RGBColor(guint8 r, guint8 g, guint8 b) : r(r), g(g), b(b) {}

RGBColor::RGBColor() {
    this->set(0,0,0);
}

RGBColor *RGBColor::set(guint8 r, guint8 g, guint8 b) {
    this->r = r;
    this->g = g;
    this->b = b;

    return this;
}
