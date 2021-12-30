#include "canvas.h"
#include "colour.h"
#include "bmp.h"

#include <string>
#include <assert.h>
#include <vector>
#include <cstdint>

using namespace canvas;

void Canvas::putPixel(const int& x, const int& y, const colour::RGB& colour)
{
    int xIndex = canvasToIndexx(x);
    int yIndex = canvasToIndexy(y);

    pixelMap.at(yIndex).at(xIndex) = colour;
}

void Canvas::pixelVector(std::vector<uint32_t>& destVector) const
{
    assert(destVector.size() == (this->w * this->h));

    int i = 0;
    for(std::vector<colour::RGB> row : this->pixelMap)
    {
        for(colour::RGB pixel : row)
        {
            destVector.at(i) = pixel.bytes();
            i++;
        }
    }
}

void Canvas::toBitmap(const std::string& filepath) const
{
    bmp::BmpImage image(this->w, this->h);
    std::vector<uint32_t> pixels((this->w * this->h), 0);

    this->pixelVector(pixels);
    image.setPixelMap(pixels);

    image.writeToFile(filepath);
}