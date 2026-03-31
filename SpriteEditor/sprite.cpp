/**
 * @file sprite.cpp
 * @brief Implementation of the Sprite class.
 *
 * This file contains the method definitions for the Sprite class.
 * A Sprite stores multiple Frame objects and manages animation data
 * such as the current frame and playback speed.
 *
 * Team: Green Goombas
 * @authors Charles Adair, Armando Calrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/29/2026 12:44AM MST by Charles Adair
 */

#include "sprite.h"

Sprite::Sprite(int width, int height) : fps{DEFAULT_FPS}, width{width}, height{height} {
    createDefaultFrame();
    frames.push_back(createDefaultFrame());
}

bool Sprite::isValidFrameIndex(int index) const
{
    return index >= 0 && index < static_cast<int>(frames.size());
}

Frame Sprite::createDefaultFrame() const
{
    Frame defaultFrame(width, height);
    return defaultFrame;
}

Sprite::Sprite() : fps{DEFAULT_FPS}, width{DEFAULT_WIDTH}, height{DEFAULT_HEIGHT}
{
}

void Sprite::removeFrame(int index)
{
    // Return if index is invalid
    if (!isValidFrameIndex(index))
        return;

    // Remove the frame at the given index
    frames.erase(frames.begin() + index);

    // If all frames were removed, create a new default blank frame
    if (frames.empty())
    {
        frames.push_back(createDefaultFrame());
    }
}

void Sprite::duplicateFrame(int index)
{
    // Return if index is invalid
    if (!isValidFrameIndex(index))
        return;

    frames.insert(frames.begin() + index + 1, frames.at(index));
}

void Sprite::moveFrame(int fromIndex, int toIndex)
{
    // Return if either index is invalid
    if (!isValidFrameIndex(fromIndex))
        return;

    if (!isValidFrameIndex(toIndex))
        return;

    // No changes if both indices are the same
    if (fromIndex == toIndex)
        return;

    // Save the frame being moved
    Frame movedFrame = frames.at(fromIndex);

    // Remove the frame from its original position
    frames.erase(frames.begin() + fromIndex);

    // Adjust index after removal
    if (fromIndex < toIndex)
        toIndex--;

    // Insert it into the new position
    frames.insert(frames.begin() + toIndex, movedFrame);
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

int Sprite::getWidth() const {
    return width;
}

int Sprite::getHeight() const {
    return height;
}

int Sprite::getFrameCount() const
{
    return static_cast<int>(frames.size());
}

void Sprite::addFrame()
{
    frames.push_back(createDefaultFrame());
}
