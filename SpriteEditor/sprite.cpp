/**
 * @file sprite.cpp
 * @brief Implementation of the Sprite class.
 *
 * This file contains the method definitions for the Sprite class.
 * A Sprite stores multiple Frame objects and manages animation data
 * such as the current frame and playback speed.
 *
 * @authors Charles Adair, Armando Calrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/26/2026 2:42PM MST by Charles Adair
 */

#include "sprite.h"

Sprite::Sprite(int width, int height) : fps(12), width(width), height(height) {
    frames.push_back(Frame(width, height));
}


void Sprite::addFrame() {
    frames.push_back(Frame(width, height));
}


void Sprite::removeFrame(int index) {
    if (index >= 0 && index < (int)frames.size()) {
        frames.erase(frames.begin() + index);
    }
}

void Sprite::duplicateFrame(int index) {
    if (index >= 0 && index < (int)frames.size()) {
        frames.insert(frames.begin() + index + 1, frames[index]);
    }
}

Frame& Sprite::getFrame(int index) {
    return frames[index];
}


void Sprite::setFPS(int newFps) {
    fps = newFps;
}

int Sprite::getFPS() const {
    return fps;
}

int Sprite::getFrameCount() const {
    return (int)frames.size();
}

int Sprite::getWidth() const {
    return width;
}

int Sprite::getHeight() const {
    return height;
}
