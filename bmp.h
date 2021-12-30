#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <fstream>
#include <vector>
#include <string>

namespace bmp
{
    constexpr int BMP_FILE_HEADER_SIZE  {14};
    constexpr int BMP_INFO_HEADER_SIZE  {40};

    constexpr int BMP_BYTES_PER_PIXEL   { sizeof(uint8_t) * 3 };
    constexpr int BMP_BITS_PER_PIXEL    { BMP_BYTES_PER_PIXEL * 8 };

    constexpr uint32_t  RGB_MASK_BLU    {0x000000FF};
    constexpr uint8_t   RGB_OFFSET_BLU  {sizeof(uint8_t) * 8 * 0};

    constexpr uint32_t  RGB_MASK_GRN    {0x0000FF00};
    constexpr uint8_t   RGB_OFFSET_GRN  {sizeof(uint8_t) * 8 * 1};

    constexpr uint32_t  RGB_MASK_RED    {0x00FF0000};
    constexpr uint8_t   RGB_OFFSET_RED  {sizeof(uint8_t) * 8 * 2};

    class BmpImage
    {
    private:
        // File info header bytes
        const char bitmapSignature[2] {'B', 'M'}; 
        uint32_t filesize;
        const uint32_t reservedBytes {0};
        const uint32_t pixelDataOffset {BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE};

        // Bitmap info header, using Windows BITMAPINFOHEADER format
        const uint32_t  infoHeaderSize {BMP_INFO_HEADER_SIZE};
        int32_t         width;                      // in pixels
        int32_t         height;                     // in pixels
        const uint16_t  numberOfColourPlanes {1};   // must == 1
        const uint16_t  colourDepth {24};           // 8bit each RGB
        const uint32_t  compressionMethod {0};      // no compression (BI_RGB)
        const uint32_t  rawImageSize {0};           // dummy value for BI_RGB
        const int32_t   hres {3780};                // pixel per metre, ~ 96 DPI
        const int32_t   vres {3780};                // pixel per metre, ~ 96 DPI
        const uint32_t  colours {0};                // 0 default to 2^n
        const uint32_t  importantColours {0};       // ignored usually

        // Pixels represented as 3 byte trios of RGB values
        std::vector<uint8_t> pixelMap;

    public:
        BmpImage(const int32_t width, const int32_t height);

        void setPixelMap(std::vector<uint32_t> pixelMap);

        int writeToFile(const std::string& filepath);
    };
}

#endif