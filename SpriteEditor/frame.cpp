/**
 * @file frame.cpp
 * @brief implementation of the Frame class.
 *
 * This class manages a 2D array of Pixel objects which represents a still image.
 *
 * @authors Charles Adair, Armando Calrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/26/2026 3:00PM MST by Charles Adair
 */
#include "frame.h"

Frame::Frame(int x, int y)
    : width(x), height(y)
{
    pixels.resize(width);
    for (int i = 0; i < width; i++) {
        pixels[i].resize(height);
    }
 }

Pixel& Frame::getPixel(int x, int y) {
    return pixels[x][y];
}

int Frame::getWidth() const {
    return width;
}

int Frame::getHeight() const {
    return height;
}

