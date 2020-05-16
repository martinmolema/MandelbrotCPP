//
// Created by martin on 28-04-20.
//

#include <thread>
#include <iostream>
#include "MyFractalArea.h"
#include "ComplexNumber.h"
#include "Palette.h"
#include "PaletteRGB.h"
#include "Rectangle.h"
#include "PaletteHSL.h"
#include <chrono>
#include <fstream>
#include <vector>
#include <iomanip>

MyFractalArea::MyFractalArea(int width, int height, int tasks_x, int tasks_y ) {
    maxIterations = 200;
    //palette = new PaletteRGB(maxIterations);
    palette = new PaletteHSL(maxIterations);
    palette->Calculate();
    this->width = width;
    this->height = height;
    this->tasks_x = tasks_x;
    this->tasks_y = tasks_y;

    color_black = new RGBColor(0, 0, 0);
}

MyFractalArea::~MyFractalArea() = default;

bool MyFractalArea::draw() {

    canvas_plane  = new Rectangle(0,0, width, height);
    fractal_plane = new Rectangle(-2, 2, 2, -2);

    fw = fractal_plane->width();
    fh = fractal_plane->height();
    cw = canvas_plane->width();
    ch = canvas_plane->height();

    ratio_x = fw / cw;
    ratio_y = fh / ch;

    n_channels            = 3;
    rowstride             = canvas_plane->width()  * n_channels; //3 bytes per pixel (RGB , 1 byte per channel)
    pixbuf_array_size     = canvas_plane->height() * rowstride;
    iterations_array_size = canvas_plane->area_size();

    iterationsArr = new iter_t[iterations_array_size];
    std::fill_n(iterationsArr, iterations_array_size, -1);

    uint64_t start_time = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count();

    int nrOfTasks_x = tasks_x;
    int nrOfTasks_y = tasks_y;

    int nrOfTasks   = nrOfTasks_x * nrOfTasks_y;
    uint64_t *times = new uint64_t[nrOfTasks];

    Rectangle **parts = new Rectangle *[nrOfTasks];
    std::thread *threads = new std::thread[nrOfTasks];

    int left = 0;
    int top  = 0;
    int slicex = canvas_plane->width()  / nrOfTasks_x; // this will yield an integer
    int slicey = canvas_plane->height() / nrOfTasks_y; // this will yield an integer

    for (int pos_x = 0; pos_x < nrOfTasks_x; pos_x++) {
        top = 0;
        for (int pos_y = 0; pos_y < nrOfTasks_y; pos_y++){
            int p = pos_y * nrOfTasks_x + pos_x;

            // determine Rectangle to calculate
            parts[p] = new Rectangle(left, top, left + slicex, top + slicey);

            // fire a thread to do the calculations
            threads[p] = std::thread(&MyFractalArea::calculatePart, this, parts[p], times, p);

            top += slicey;
        }
        left += slicex;
    }
    for (int i = 0; i < nrOfTasks; i++) {
        threads[i].join();
        //std::cout << "Task finished: " << i << "\n";
    }
    //calculatePart(canvas_plane);

    assignColors();

    uint64_t end_time = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count();

    std::cout << "Total fractal area = (" << width << "," <<  height << ") = " << std::fixed << std::setprecision(2) << (width*height) / 1024.0f / 1024.0f << "Mpx" << std::endl;
    std::cout << "Thread area size = (" << slicex << "," <<  slicey << ")" << std::endl;
    std::cout << "Threads : " << nrOfTasks_x << " x " << nrOfTasks_y << "= " << nrOfTasks << std::endl;
    std::cout << "Calculate time = " << std::right << std::setw(5) <<  end_time - start_time << "ms"  << std::endl;
    std::cout << std::setprecision(0);
    for(int i=0;i<nrOfTasks;i++) {
        std::cout << "thread time [" << std::right << std::setw(2) << i << std::left  << "] = "
        << std::right << std::setw(5) << times[i] << std::left << "ms | Area("
        << parts[i]->x1 << "," << parts[i]->y1 << ")-("
        << parts[i]->x2 << "," << parts[i]->y2 << ")"
        << std::endl;
    }

    return true;
}

long  MyFractalArea::calculatePart(Rectangle *part, uint64_t times[], int threadnr) {
    uint64_t start_time = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count();

    ComplexNumber c(0, 0);
    int x1 = (int)part->x1;
    int x2 = (int)part->x2;
    int y1 = (int)part->y1;
    int y2 = (int)part->y2;

    complex_base_type fx1 = fractal_plane->x1;
    complex_base_type fy1 = fractal_plane->y1;


    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++)
        {
            int iterations = 0;
            bool hasConverged = false;
            bool needsMoreIterations = false;
            bool isStable = false;
            complex_base_type cx, cy;

            // calculate the place on the fractal-plane using a complex number C = (cx,cy); calculated from the (x,y) position on the canvas-plance
            cx = fx1 + (complex_base_type) x * ratio_x;
            cy = fy1 - (complex_base_type) y * ratio_y;

            c.set(cx, cy);

            bool inCircle = c.calculateDistanceSquared(*zeroCenter) < (2 * 2);

            if (inCircle) {
                complex_base_type distToPrevious;

                ComplexNumber start(0, 0);
                ComplexNumber previous(start);

                do {
                    start.sqr()->add(c);
                    distToPrevious = start.calculateDistanceSquared(previous);

                    hasConverged = distToPrevious < (0.00003 * 0.00003);
                    needsMoreIterations = (++iterations) < maxIterations;

                    isStable = start.calculateDistanceSquared(*zeroCenter) < 4;

                    previous.copyFrom(start);

                } while (needsMoreIterations && isStable && !hasConverged);

                long p = canvas_plane->arrayposition(x,y);
                //std::cout << p << std::endl;
                iterationsArr[p] = (isStable) ? -1 : iterations;

            }// if in the inner circle
        }// for y
    }//for x
    uint64_t end_time = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count();

    times[threadnr] = end_time - start_time;

    return end_time - start_time ;
}

bool MyFractalArea::assignColors() {
    localPixBuf = new guint8[pixbuf_array_size];
    long pixbufcounter = 0;

    for(int i=0;i<iterations_array_size;i++){
        iter_t iteration = iterationsArr[i];

        RGBColor *color;
        if (iteration == -1) {
            color = color_black;
        }
        else{
            color = (*palette)[iteration];
        }
        localPixBuf[pixbufcounter++] = color->r;   // Red
        localPixBuf[pixbufcounter++] = color->g;   // Green
        localPixBuf[pixbufcounter++] = color->b;   // Blue
    }
    return true;
}// assignColors

bool MyFractalArea::save(std::string filename){
    std::ofstream myfile;
    uint64_t start_time = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count();


    myfile.open(filename, std::ios::out | std::ios::trunc);
    myfile << "P6" << std::endl << width << " "  << height << std::endl << "255" << std::endl;

    for (int i;i < pixbuf_array_size;i++){
        myfile << localPixBuf[i];
    }
    myfile.close();

    uint64_t end_time = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "Save time = " << end_time - start_time << "ms"  << std::endl;


}