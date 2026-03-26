#include "frame.h"

Frame::Frame(QObject *parent)
    : QObject{parent}
{
    width = 16;
    height = 16;
 }

// Frame::Frame(int width, int height){

//     this->width = width;
//     this->height = height;

//     std::vector<int> defaultColor {255, 255, 255, 1};

//     for (int i = 0; i < width; i++ ){
//         for(int z = 0; z < height; z++){

//             pixels[i][z].setColor(defaultColor);

//         }
//     }

std::vector<int> Frame::getPixelColor(int x, int y) {
    if (x > width || y > height) {
        throw std::invalid_argument("Index is out of bounds.");
    };
    return pixels[x][y].getColor();
}

void Frame::setPixelColor(int x, int y, std::vector<int> color) {
    if (x > width || y > height) {
        throw std::invalid_argument("Index is out of bounds.");
    };
    pixels[x][y].setColor(color);
}

void Frame::setResolution(int w, int h) {
    width = w;
    height = h;
}

