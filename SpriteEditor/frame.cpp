#include "frame.h"

Frame::Frame(QObject *parent, int x, int y)
    : QObject{parent}, width(x), height(y)
{
    pixels.resize(width);
    for (int i = 0; i < width; i++) {
        pixels[i].resize(height);
    }
 }

Pixel& Frame::getPixel(int x, int y) {
    return pixels[x][y];
}

