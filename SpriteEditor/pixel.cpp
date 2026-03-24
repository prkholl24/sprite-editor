#include "pixel.h"

pixel::pixel(QObject *parent)
    : QObject{parent}
{}

pixel::pixel(std::vector<int> color){
    this->color = color;

}

void pixel::setColor(std::vector<int> newColor){
    color = newColor;

}
