/**
 * @file sprite.cpp
 * @brief implementation of the Sprite class.
 *
 * This class manages a collection of Frame objects and controls animation
 * behavior such as frame order and grames per second.
 * It also tracks the currently active frame.
 *
 * @authors Charles Adair, Armando Calrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/26/2026 2:42PM MST by Charles Adair
 */
#include "sprite.h"

Sprite::Sprite(int width, int height) : width(width), height{height} {
    frames.push_back(Frame());
}


void Sprite::addFrame() {
    frames.push_back(Frame());
}


void Sprite::removeFrame(int index) {
    frames.erase(frames.begin() + index);
    frames.shrink_to_fit();
}

Frame& Sprite::getFrame(int index) {
    return frames[index];
}


void Sprite::setFPS(int newFps) {
    fps = newFps;
}

int Sprite::getFrameCount() const {
    return frames.size();
}
