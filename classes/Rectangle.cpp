//
// Created by martin on 29-04-20.
//

#include <cstdlib>
#include "Rectangle.h"
#include "Dimension.h"

Rectangle::Rectangle(double x1, double y1, double x2, double y2){
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;

  this->w = abs(this->x2 - this->x1);
  this->h = abs(this->y2 - this->y1);
}

Rectangle *Rectangle::fitInOther(const Rectangle & other) {
    return this;
}

double Rectangle::ratioXY() {
    return w/h;
}

double Rectangle::ratioYX() {
    return h/w;
}

double Rectangle::width() {
    return w;
}

double Rectangle::height() {
    return h;
}

Dimension *Rectangle::dimension(){
    Dimension *d = new Dimension(w,h);
    return d;
}

double Rectangle::area_size(){
    return dimension()->area_size();
}

long Rectangle::arrayposition(double x, double y) {
    return x + (y * w);
}
