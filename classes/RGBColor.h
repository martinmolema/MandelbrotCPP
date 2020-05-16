//
// Created by martin on 29-04-20.
//

#ifndef MANDELGLADE_RGBCOLOR_H
#define MANDELGLADE_RGBCOLOR_H


typedef unsigned char guint8;

class RGBColor {
public:
    guint8 r,g,b;
    RGBColor();
    RGBColor(guint8 r, guint8 g, guint8 b);
    RGBColor *set(guint8 r, guint8 g, guint8 b);
};


#endif //MANDELGLADE_RGBCOLOR_H
