//
// Created by martin on 29-04-20.
//

#ifndef MANDELGLADE_DIMENSION_H
#define MANDELGLADE_DIMENSION_H

class Rectangle;

class Dimension {
public:
    Dimension(double w, double h);
    Dimension(double x1, double y1, double x2, double y2);
    Dimension(Rectangle r);

    double getW() const;
    double getH() const;
    double area_size() const;
private:
    double w,h;
};


#endif //MANDELGLADE_DIMENSION_H
