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

Pixel::Pixel(const std::vector<int>& color){
    this->color = {0,0,0,0}; // Default
    setColor(color);
}

Pixel::Pixel(const Pixel& px){
    color = px.getColor();
}

Pixel& Pixel::operator=(const Pixel& px){
    if (this != &px) {
        color = px.getColor();
    }
    return *this;
}

void Pixel::setColor(const std::vector<int>& newColor){
    if (newColor.size() != 4) {
        return;
    }
    for (int val : newColor) {
        if (val < 0 || val > 255) {
            return;
        }
    }
    color = newColor;
}

void Pixel::setOpacity(int opacity){
    if (opacity < 0 || opacity > 255) {
        return;
    }
    if (this->color.size() >= 4){
        this->color[3] = opacity;
    }
}

std::vector<int> Pixel::getColor() const {
    return this->color;
}


