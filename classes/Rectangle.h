//
// Created by martin on 29-04-20.
//

#ifndef MANDELGLADE_RECTANGLE_H
#define MANDELGLADE_RECTANGLE_H


#include "Dimension.h"

class Dimension;

class Rectangle {
public:
    Rectangle(double x1, double y1, double x2, double y2);

    double x1,y1,x2,y2, w, h;

    Dimension *dimension();
    double width();
    double height();
    Rectangle *fitInOther(const Rectangle &other);
    double ratioXY();
    double ratioYX();

    double area_size();

    long arrayposition(double x, double y);
private:
};


#endif //MANDELGLADE_RECTANGLE_H
