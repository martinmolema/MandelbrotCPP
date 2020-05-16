//
// Created by martin on 29-04-20.
//

#ifndef MANDELGLADE_PALETTERGB_H
#define MANDELGLADE_PALETTERGB_H


#include "Palette.h"

class PaletteRGB : public Palette {
public:
    PaletteRGB(int maxIterations);
    virtual Palette *Calculate() override;

private:
    const unsigned long int RGB_FILTER_R = (255 << 16);
    const unsigned long int RGB_FILTER_G = (255 << 8);
    const unsigned long int RGB_FILTER_B = (255);

    const double maxRange = 255*255*255;
};


#endif //MANDELGLADE_PALETTERGB_H
