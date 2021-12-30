#ifndef CANVAS_H
#define CANVAS_H

#include "colour.h"
#include "bmp.h"

#include <vector>
#include <string>
#include <assert.h>

namespace canvas
{

class Canvas
{
private:
    const int w;
    const int h;
    std::vector< std::vector<colour::RGB> > pixelMap;

    int canvasToIndexx(int x) { return (w / 2) + x; }
    int canvasToIndexy(int y) { return (h / 2) + y; }

    void pixelVector(std::vector<uint32_t>& destVector) const;

public:
    Canvas(int width, int height, colour::RGB bg = colour::RGB(0xFFFFFF))
        : w {width}
        , h {height}
        , pixelMap { static_cast<long unsigned int>(height), std::vector<colour::RGB>(width, bg) } {}

    int getWidth() const { return this->w; }
    int getHeight() const { return this->h; }

    void putPixel(const int& x, const int& y, const colour::RGB& colour);

    void toBitmap(const std::string& filepath) const;
};

}

#endif