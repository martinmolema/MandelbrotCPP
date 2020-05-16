//
// Created by martin on 29-04-20.
//

#include <cmath>
#include "Palette.h"

Palette::Palette(int maxIterations) {
    this->maxIterations = maxIterations;
    colors = new RGBColor* [maxIterations+1]; //using the default constructor here! 0-200 INCLUSIVE because last color must be accessible
    for(int i=0;i<=maxIterations;i++) colors[i] = new RGBColor(0,0,0);
}

Palette* Palette::Calculate() {
    return this;
}

/**
 * assigns the offset : starting position in the palet space. will cycle (using modulo) between 0-100.
 * @param offset value between 0-100 (meaning a percentage of the total available palet space)
 * @return
 */
Palette* Palette::setOffset(double offset) {
    this->offset = std::fmod(offset , 100.0);
    return this;
}

RGBColor *Palette::get_color(int position) {
    return colors[position];
}


RGBColor *Palette::set_color(int position, guint8 r,guint8 g,guint8 b) {
    RGBColor *rgb =  colors[position];
    rgb->set( r,g,b);
    return rgb;
}

RGBColor *Palette::operator [](int position){
    return get_color(position);
}
