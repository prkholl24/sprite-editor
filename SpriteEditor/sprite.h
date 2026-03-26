/**
 * @file sprite.h
 * @brief Declaration of the Sprite class.
 *
 * This class manages a collection of Frame objects and controls animation
 * behavior such as frame order and grames per second.
 * It also tracks the currently active frame.
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/26/2026 3:01PM MST by Charles Adair
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "frame.h"

/**
 * @brief Represents an animated sprite composed of multiple frames.
 *
 *This class manages a collection of frames and playback settings.
 */
class Sprite {
private:

    /**
     * @brief Frames is  a set of 2D arrays containing color data ordered by
     * the sequence in which they are played back.
     */
    std::vector<Frame> frames;

    /**
     * @brief Frame rate at which the playback occurs
     */
    int fps;

    /**
     * @brief width of the Sprite animation
     */
    const int width;

    /**
     * @brief height of the Sprite animation
     */
    const int height;

public:

    /**
     * @brief Constructs a sprite with a default frame.
     */
    Sprite(int width = 16, int height = 16);

    /**
     * @brief Adds a new frame
     */
    void addFrame();

    /**
     * @brief Removes a frame
     * @param The index of the frame to be removed.
     */
    void removeFrame(int index);

    /**
     * @brief Removes a frame
     * @param index Frame index
     */
    void duplicateFrame(int index);

    /**
     * @brief Gets the current frame
     *
     * @param index of current frame
     * @return Reference to the current frame
     */
    Frame& getFrame(int index);

    /**
     * @brief Gets the playback  frames per second
     *
     * @param fps New FPS value
     */
    int getFPS() const;

    /**
     * @brief Sets a new playback speed
     * @param The new speed measured in Frames Per Second (FPS).
     */
    void setFPS(int newFPS);

    /**
     * @brief Gets total frame count.
     * @return number of frames
     */
    int getFrameCount() const;
};

#endif // SPRITE_H
