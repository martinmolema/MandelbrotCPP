//
// Created by martin on 29-04-20.
//

#ifndef MANDELGLADE_PALETTE_H
#define MANDELGLADE_PALETTE_H


#include "RGBColor.h"

class Palette {
public:
    Palette(int maxIterations);
    Palette *setOffset(double offset);
    virtual Palette *Calculate();
    RGBColor *get_color(int position);
    RGBColor *set_color(int position, guint8 r,guint8 g,guint8 b);

    RGBColor *operator [](int position);
protected:
    double maxIterations;
    // Percentage of the total palette range available
    double offset;
    RGBColor **colors;
};


#endif //MANDELGLADE_PALETTE_H
