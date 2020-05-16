cmake_minimum_required(VERSION 3.15)
project(mandelcpp)

#[[
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3MM REQUIRED gtkmm-3.0)

include_directories(${GTK3MM_INCLUDE_DIRS})
link_directories(${GTK3MM_LIBRARY_DIRS})

add_definitions(${GTK3MM_CFLAGS_OTHER})


]]
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(mandelcpp mandelcpp.cpp classes/MyFractalArea.cpp classes/MyFractalArea.h classes/ComplexNumber.cpp classes/ComplexNumber.h classes/Rectangle.cpp classes/Rectangle.h classes/Palette.cpp classes/Palette.h classes/PaletteRGB.cpp classes/PaletteRGB.h classes/PaletteHSL.cpp classes/PaletteHSL.h classes/Dimension.cpp classes/Dimension.h classes/RGBColor.cpp classes/RGBColor.h)
target_link_libraries(mandelcpp Threads::Threads)
