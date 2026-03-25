#include "frame.h"

Frame::Frame(QObject *parent)
    : QObject{parent}
{}

Pixel& Frame::getPixel(int x, int y) {
    return pixels[x][y];
}

void Frame::setPixel(int x, int y, Pixel& p) {
    pixels[x][y] = p;
}

// void Frame::setResolution() {

// }
