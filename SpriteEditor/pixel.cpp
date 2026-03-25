#include "pixel.h"

Pixel::Pixel(QObject *parent)
    : QObject{parent}
{}

Pixel::Pixel(std::vector<int>& color){
    this->color = color;

}

Pixel::Pixel(Pixel& px){

    color = px.getColor();

}

void Pixel::operator=(Pixel& px){
    color = px.getColor();
}

void Pixel::setColor(std::vector<int>& newColor){
    color = newColor;

}

void Pixel::setOpacity(int opacity){
    if (this->color[3]){
        this->color[3] = opacity;
    }
}

std::vector<int>& Pixel::getColor(){
    return this->color;
}


