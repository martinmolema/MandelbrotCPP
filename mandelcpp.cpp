#include "classes/MyFractalArea.h"


int main(int argc, char *argv[]) {

    MyFractalArea fractal(1600,1600,8,8);
    //MyFractalArea fractal(200,200,1,1);

    fractal.draw();
    fractal.save("/home/martin/mandelbrot.ppm");

    return 0;
}

