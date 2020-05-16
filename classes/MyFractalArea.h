//
// Created by martin on 28-04-20.
//

#ifndef MANDELGLADE_MYFRACTALAREA_H
#define MANDELGLADE_MYFRACTALAREA_H

#include "PaletteRGB.h"
#include "ComplexNumber.h"
#include "Rectangle.h"
#include <string>
#include <vector>

typedef int iter_t;

class MyFractalArea  {
public:
    MyFractalArea(int width, int height, int tasks_x, int tasks_y );
    virtual ~MyFractalArea();
    bool draw () ;
    bool save(std::string filename);

protected:
    long calculatePart(Rectangle *part, uint64_t times[], int threadnr);
    bool assignColors();

    int width, height, tasks_x, tasks_y;

    Rectangle *fractal_plane, *canvas_plane;
    guint8 *localPixBuf = nullptr;
    iter_t *iterationsArr = nullptr;
    int maxIterations;
    Palette *palette;
    int n_channels;
    int rowstride;
    long pixbuf_array_size;
    long iterations_array_size;

    RGBColor *color_black;
    complex_base_type fw, fh, cw,ch;

    complex_base_type ratio_x, ratio_y;
    ComplexNumber *zeroCenter = new ComplexNumber(0, 0);

    double paletOffset = 0;


};


#endif //MANDELGLADE_MYFRACTALAREA_H
