#ifndef COLOUR_H
#define COLOUR_H

#include <cstdint>
#include <iostream>

namespace colour
{

constexpr int RGB_RED_MASK {0xFF0000};
constexpr int RGB_GRN_MASK {0x00FF00};
constexpr int RGB_BLU_MASK {0x0000FF};

constexpr int RGB_RED_OFFSET { sizeof(uint8_t) * 8 * 2};
constexpr int RGB_GRN_OFFSET { sizeof(uint8_t) * 8 * 1};
constexpr int RGB_BLU_OFFSET { sizeof(uint8_t) * 8 * 0};

constexpr int RGB_CHANNEL_MAX {0xFF};

class RGB
{
private:
    uint8_t red;
    uint8_t grn;
    uint8_t blu;

public:
    // Constructor: specify red, green and blue bytes in separate arguments
    RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        : red {r}, grn {g}, blu {b} {}

    // Constructor: specify 3-byte RGB value
    // e.g. RGB(0x00FF00) is green
    RGB(int rgb)
        : red { static_cast<uint8_t>((rgb & RGB_RED_MASK) >> RGB_RED_OFFSET) }
        , grn { static_cast<uint8_t>((rgb & RGB_GRN_MASK) >> RGB_GRN_OFFSET) }
        , blu { static_cast<uint8_t>((rgb & RGB_BLU_MASK) >> RGB_BLU_OFFSET) } {}

    // getters
    uint8_t channel_red() const { return this->red; }
    uint8_t channel_grn() const { return this->grn; }
    uint8_t channel_blu() const { return this->blu; }

    // Returns an integer holding the RGB values in the lowest 3 bytes
    // in order from lowest: blue, green, red
    int bytes();

};

RGB operator+(const RGB& left, const RGB& right);
RGB operator*(const int& mul, const RGB& rgb);
RGB operator*(const float& mul, const RGB& rgb);
RGB operator*(const double& mul, const RGB& rgb);
std::ostream& operator<<(std::ostream& out, const RGB& rgb);

}


#endif