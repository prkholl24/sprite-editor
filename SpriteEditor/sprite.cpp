/**
 * @file sprite.cpp
 * @brief Implementation of the Sprite class.
 *
 * This file contains the method definitions for the Sprite class.
 * A Sprite stores multiple Frame objects and manages animation data
 * such as the current frame and playback speed.
 *
 * @authors Charles Adair, Armando Carillo, Parker Hollingsed, Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3-26-2026
 */

#include "sprite.h"

bool Sprite::isValidIndex(int index) const
{
    return index >= 0 && index < frames.size();
}

Frame Sprite::makeDefaultFrame() const
{
    Frame defaultFrame;
    defaultFrame.setResolution(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    return defaultFrame;
}

Sprite::Sprite()
{
    fps = DEFAULT_FPS;
    currentFrameIndex = 0;
    frames.push_back(makeDefaultFrame());
}

void Sprite::addFrame(const Frame& frame)
{
    frames.push_back(frame);
}

void Sprite::removeFrame(int index)
{
    // Check for invalid index
    if (!isValidIndex(index))
        return;

    // Remove the frame at the given index
    frames.erase(frames.begin() + index);

    // If all frames were removed, create a new default blank frame
    if (frames.empty())
    {
        frames.push_back(makeDefaultFrame());
        currentFrameIndex = 0;
    }
    // If currentFrameIndex is now past the end, move it back
    else if (currentFrameIndex >= frames.size())
    {
        currentFrameIndex = frames.size() - 1;
    }
}

void Sprite::duplicateFrame(int index)
{
    // Check for invalid index
    if (!isValidIndex(index))
        return;

    frames.insert(frames.begin() + index + 1, frames[index]);
}

void Sprite::moveFrame(int fromIndex, int toIndex)
{
    // Check for invalid indices
    if (!isValidIndex(fromIndex))
        return;

    if (!isValidIndex(toIndex))
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

    // Keep currentFrameIndex pointing to the same frame after the move
    if (currentFrameIndex == fromIndex)
    {
        currentFrameIndex = toIndex;
    }
    else if (fromIndex < currentFrameIndex && toIndex >= currentFrameIndex)
    {
        currentFrameIndex--;
    }
    else if (fromIndex > currentFrameIndex && toIndex <= currentFrameIndex)
    {
        currentFrameIndex++;
    }
}

Frame& Sprite::getCurrentFrame()
{
    return frames.at(currentFrameIndex);
}

int Sprite::getCurrentFrameIndex() const
{
    return currentFrameIndex;
}

Frame& Sprite::getFrame(int index)
{
    return frames.at(index);
}

int Sprite::getFPS() const
{
    return fps;
}

void Sprite::setFPS(int fps)
{
    if (fps > 0)
        this->fps = fps;
}

int Sprite::getFrameCount() const
{
    return frames.size();
}
