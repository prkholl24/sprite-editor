#include "pixel.h"

pixel::pixel(QObject *parent)
    : QObject{parent}
{}

pixel::pixel(std::vector<int>& color){
    this->color = color;

}

void pixel::setColor(std::vector<int>& newColor){
    color = newColor;

}

void pixel::setOpacity(int opacity){
    if (this->color[3]){
        this->color[3] = opacity;
    }
}

std::vector<int>& pixel::getColor(){
    return this->color;
}
