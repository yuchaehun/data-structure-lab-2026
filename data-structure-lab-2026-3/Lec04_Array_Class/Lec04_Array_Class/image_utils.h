#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <array>

// Use constexpr instead of #define for modern C++
constexpr int HEIGHT = 8;
constexpr int WIDTH = 8;

// Alias for a 2D array based on std::array for readability
using Image2D = std::array<std::array<int, WIDTH>, HEIGHT>;

// Declaration of function to get maximum pixel brightness
int getMaxBrightness(const Image2D& img);

#endif // IMAGE_UTILS_H