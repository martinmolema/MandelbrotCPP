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

    // the palette used (have a look at the constructor to select a different palette
    Palette *palette;

    // array length of the RGB-pixel colors. 3 positions per pixel for (R,G,B)
    long pixbuf_array_size;

    // the number of pixels in the virtual canvas
    long iterations_array_size;

    // the inner color of the Mandelbrot fractal is black; this color is created once.
    RGBColor *color_black = new RGBColor(0,0,0);

    complex_base_type ratio_x, ratio_y;
    ComplexNumber *zeroCenter = new ComplexNumber(0, 0);

};


#endif //MANDELGLADE_MYFRACTALAREA_H
