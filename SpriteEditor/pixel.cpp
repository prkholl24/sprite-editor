/**
 * @file pixel.cpp
 * @brief implementation of the Pixel class.
 *
 * This class represents a Pixel which contains color data
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/26/2026 2:42PM MST by Charles Adair
 */

#include "pixel.h"

Pixel::Pixel() {
    color = {0,0,0,0};
}

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

std::vector<int> const Pixel::getColor(){
    return this->color;
}


