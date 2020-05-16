//
// Created by martin on 29-04-20.
//

#include "PaletteRGB.h"

PaletteRGB::PaletteRGB(int maxIterations) : Palette(maxIterations) {}

Palette *PaletteRGB::Calculate() {
    for (int j = 0; j <= maxIterations; j++) {
        double ratio = (double)j / (double) maxIterations;
        long ratedRatio = ratio * maxRange; // integer needed!

        ratedRatio += ((double)offset / (double) 100) * maxRange;
        ratedRatio = ratedRatio % (long) maxRange;

        guint8 r = (ratedRatio & RGB_FILTER_R) >> 16;
        guint8 g = (ratedRatio & RGB_FILTER_G) >> 8;
        guint8 b = (ratedRatio & RGB_FILTER_B);

        set_color(j, r,g,b);
    }
    return this;
}// Calculate()
