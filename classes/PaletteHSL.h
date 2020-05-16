//
// Created by martin on 29-04-20.
//

#ifndef MANDELGLADE_PALETTEHSL_H
#define MANDELGLADE_PALETTEHSL_H


#include "Palette.h"

class PaletteHSL : public Palette {
public:
    PaletteHSL(int maxIterations);
    Palette *Calculate() override;
    RGBColor * hslToRgb(double hue, double sat, double light);
    double hueToRgb(double t1, double t2, double hue);

protected:
    double _lightness = 0.5;
    double _saturation = 1.0;
};


#endif //MANDELGLADE_PALETTEHSL_H
