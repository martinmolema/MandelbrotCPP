#include "classes/MyFractalArea.h"


int main(int argc, char *argv[]) {

    //MyFractalArea fractal(1600,1600,4,4);
    MyFractalArea fractal(1600,1600,8,8);

    fractal.draw();
    fractal.save("/home/martin/mandelbrot.ppm");

    return 0;
}

