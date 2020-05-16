//
// Created by martin on 29-04-20.
//

#include <cmath>
#include "PaletteHSL.h"

PaletteHSL::PaletteHSL(int maxIterations) : Palette(maxIterations) {

}

Palette *PaletteHSL::Calculate() {
    // offset is always modulo 100!

    for (int j = 0; j <= this->maxIterations; j++) {
        // calculate the relative position from J regarding the max-iterations and offset it a bit with a given value
        double dblHue =
                (double) this->offset / 100.0
                +
                (double) (j / (double) this->maxIterations);
        dblHue = std::fmod(dblHue * 360, 360);

        double saturation = this->_saturation;
        double lightness = this->_lightness;

        colors[j] = this->hslToRgb(dblHue, saturation, lightness);
    }
    return this;
}

RGBColor * PaletteHSL::hslToRgb(double hue, double sat, double light) {
    double t1, t2, r, g, b;

    hue = hue / 60;

    if (light <= 0.5) {
        t2 = light * (sat + 1);
    } else {
        t2 = light + sat - (light * sat);
    }
    t1 = light * 2 - t2;
    r = round(this->hueToRgb(t1, t2, hue + 2) * 255);
    g = round(this->hueToRgb(t1, t2, hue) * 255);
    b = round(this->hueToRgb(t1, t2, hue - 2) * 255);
    return new RGBColor(r,g,b);
}

/*
Convert a HSL-Hue to RGB value
 */
double PaletteHSL::hueToRgb(double t1,double  t2,double  hue) {
    if (hue < 0) hue += 6;
    if (hue >= 6) hue -= 6;
    if (hue < 1) return (t2 - t1) * hue + t1;
    else if (hue < 3) return t2;
    else if (hue < 4) return (t2 - t1) * (4 - hue) + t1;
    else return t1;
}
