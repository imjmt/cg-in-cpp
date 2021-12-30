#include "colour.h"

#include <algorithm>

using namespace colour;

int RGB::bytes()
{
    int bytes {0};

    bytes |= ((this->red) << RGB_RED_OFFSET);
    bytes |= ((this->grn) << RGB_GRN_OFFSET);
    bytes |= ((this->blu) << RGB_BLU_OFFSET);

    return bytes;
}

RGB colour::operator+(const RGB& left, const RGB& right)
{
    // int working values, so we can detect overflow and clamp it
    int r, g, b;

    r = static_cast<int>(left.channel_red()) + static_cast<int>(right.channel_red());
    r = static_cast<uint8_t>(r > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : r);

    g = static_cast<int>(left.channel_grn()) + static_cast<int>(right.channel_grn());
    g = static_cast<uint8_t>(g > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : g);

    b = static_cast<int>(left.channel_blu()) + static_cast<int>(right.channel_blu());
    b = static_cast<uint8_t>(b > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : b);

    return RGB(r, g, b);
}

RGB colour::operator*(const int& mul, const RGB& rgb)
{
    // Can't have negative colours
    if(mul <= 0) { return RGB(0, 0, 0); }

    int r, g, b;

    r = mul * static_cast<int>(rgb.channel_red());
    r = static_cast<uint8_t>(r > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : r);

    g = mul * static_cast<int>(rgb.channel_grn());
    g = static_cast<uint8_t>(g > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : g);

    b = mul * static_cast<int>(rgb.channel_blu());
    b = static_cast<uint8_t>(b > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : b);

    return RGB(r, g, b);
}

RGB colour::operator*(const float& mul, const RGB& rgb)
{
    // Can't have negative colours
    if(mul <= 1e-6f) { return RGB(0, 0, 0); }

    int r, g, b;

    r = static_cast<int>(mul * static_cast<float>(rgb.channel_red()));
    r = static_cast<uint8_t>(r > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : r);

    g = static_cast<int>(mul * static_cast<float>(rgb.channel_grn()));
    g = static_cast<uint8_t>(g > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : g);

    b = static_cast<int>(mul * static_cast<float>(rgb.channel_blu()));
    b = static_cast<uint8_t>(b > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : b);

    return RGB(r, g, b);
}

RGB colour::operator*(const double& mul, const RGB& rgb)
{
    // Can't have negative colours
    if(mul <= 1e-6f) { return RGB(0, 0, 0); }

    int r, g, b;

    r = static_cast<int>(mul * static_cast<double>(rgb.channel_red()));
    r = static_cast<uint8_t>(r > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : r);

    g = static_cast<int>(mul * static_cast<double>(rgb.channel_grn()));
    g = static_cast<uint8_t>(g > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : g);

    b = static_cast<int>(mul * static_cast<double>(rgb.channel_blu()));
    b = static_cast<uint8_t>(b > RGB_CHANNEL_MAX ? RGB_CHANNEL_MAX : b);

    return RGB(r, g, b);
}

std::ostream& colour::operator<<(std::ostream& out, const RGB& rgb)
{
    out << "RGB(";
    out << static_cast<int>(rgb.channel_red()) << ", ";
    out << static_cast<int>(rgb.channel_grn()) << ", ";
    out << static_cast<int>(rgb.channel_blu()) << ")";

    return out;
}
