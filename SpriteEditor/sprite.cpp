/**
 * @file sprite.cpp
 * @brief implementation of the Sprite class.
 *
 * This class manages a collection of Frame objects and controls animation
 * behavior such as frame order and grames per second.
 * It also tracks the currently active frame.
 *
 * @authors
 * @date
 */
#include "sprite.h"

sprite::sprite(QObject *parent)
    : QObject{parent}
{}

/**
 * @brief Adds a new frame to the end of the frame array.
 * @param The frame you want to add
 */
void sprite::addFrame(Frame f) {
    frames.push_back(f);
}

/**
 * @brief Removes the desired frame from the frame array.
 * @param The index of the frame to delete
 */
void sprite::removeFrame(int index) {
    frames.erase(frames.begin() + index);
    frames.shrink_to_fit();
}

/**
 * @brief getCurrentFrame - Gets the desired frame
 * @return
 */
Frame sprite::getFrame(int index) {
    return frames[index];
}

void sprite::setFPS(int newFps) {
    fps = newFps;
}

int sprite::getFrameCount() {
    return frames.size();
}
