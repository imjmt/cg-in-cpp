#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "bmp.h"

using namespace std;

bmp::BmpImage::BmpImage(const int32_t width, const int32_t height)
{
    long rowSize;
    uint32_t pixelMapLength;

    this->width = width;
    this->height = height;

    // Calculate size of pixel rows, including padding to multiple
    // of 32-bit DWORD
    rowSize = ((BMP_BITS_PER_PIXEL * abs(this->width) + 31)/32) * 4;

    // Calculate bmp file size including headers and pixel map
    pixelMapLength = rowSize * abs(height);
    this->filesize = pixelMapLength;
    this->filesize += BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE;

    // Initialise pixel map with 0 values
    this->pixelMap = vector<uint8_t>(pixelMapLength, 0);
}

void bmp::BmpImage::setPixelMap(vector<uint32_t> pixelMap)
{
    assert(pixelMap.size() == abs(this->width * this->height));

    long rowSize { ((BMP_BITS_PER_PIXEL * abs(this->width) + 31)/32) * 4 };
    
    // Calculate bytes of padding per row required
    // This is equal to the inverse of the number of pixel bytes in the row mod 4
    int paddingBytes { (BMP_BYTES_PER_PIXEL * abs(this->width)) % 4 };
    switch(paddingBytes)
    {
        case 1:
            paddingBytes = 3;
            break;
        case 3:
            paddingBytes = 1;
            break;
    };

    int y;
    int x;
    int padding;
    uint8_t r, g, b;
    for(y = 0; y < abs(this->height); y++)
    {
        for(x = 0; x < abs(this->width); x++)
        {
            r = static_cast<uint8_t>((pixelMap.at(y*abs(this->width) + x) & RGB_MASK_RED) >> RGB_OFFSET_RED);
            g = static_cast<uint8_t>((pixelMap.at(y*abs(this->width) + x) & RGB_MASK_GRN) >> RGB_OFFSET_GRN);
            b = static_cast<uint8_t>((pixelMap.at(y*abs(this->width) + x) & RGB_MASK_BLU) >> RGB_OFFSET_BLU);

            this->pixelMap.at(y*rowSize + 3*x) = b;
            this->pixelMap.at(y*rowSize + 3*x + 1) = g;
            this->pixelMap.at(y*rowSize + 3*x + 2) = r;
        }

        padding = paddingBytes;
        x *= 3;
        while(padding)
        {
            this->pixelMap.at(x++) = 0;
            padding--;
        }
    }

}
int bmp::BmpImage::writeToFile(const string& filepath)
{
    // Try to open file at filepath
    ofstream fout {filepath};
    if (!fout) { return -1; }

    // Write the file header
    fout.write(this->bitmapSignature, 2);
    fout.write((char*)&this->filesize, sizeof(uint32_t));
    fout.write((char*)&this->reservedBytes, sizeof(uint32_t));
    fout.write((char*)&this->pixelDataOffset, sizeof(uint32_t));

    // Write the info header
    fout.write((char*)&this->infoHeaderSize, sizeof(uint32_t));
    fout.write((char*)&this->width, sizeof(int32_t));
    fout.write((char*)&this->height, sizeof(int32_t));
    fout.write((char*)&this->numberOfColourPlanes, sizeof(uint16_t));
    fout.write((char*)&this->colourDepth, sizeof(uint16_t));
    fout.write((char*)&this->compressionMethod, sizeof(uint32_t));
    fout.write((char*)&this->rawImageSize, sizeof(uint32_t));
    fout.write((char*)&this->hres, sizeof(int32_t));
    fout.write((char*)&this->vres, sizeof(int32_t));
    fout.write((char*)&this->colours, sizeof(uint32_t));
    fout.write((char*)&this->importantColours, sizeof(uint32_t));

    fout.write((char*)(this->pixelMap.data()), this->pixelMap.size());

    return this->filesize;
}