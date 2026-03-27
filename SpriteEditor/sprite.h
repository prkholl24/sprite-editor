/**
 * @file sprite.h
 * @brief Declaration of the Sprite class.
 *
 * This class manages a collection of Frame objects and controls animation
 * behavior such as frame order and frames per second.
 * It also tracks the currently active frame.
 *
 * @authors Charles Adair, Armando Carillo, Parker Hollingsed, Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3-26-2026
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "frame.h"

/**
 * @class Sprite
 * @brief Represents an animated sprite composed of multiple frames.
 *
 * The Sprite class stores a sequence of Frame objects that together form
 * an animation. It also stores the current frame index and the playback
 * speed used for previewing the animation.
 */
class Sprite
{
public:

    /**
     * @brief Default constructor for Sprite.
     *
     * Initializes a sprite with one default frame, a default FPS value,
     * and the current frame index set to 0.
     */
    Sprite();

    /**
     * @brief Adds a new frame to the sprite.
     *
     * Appends a frame to the list of frames in the sprite.
     *
     * @param frame The frame to add.
     */
    void addFrame(const Frame& frame);

    /**
     * @brief Removes a frame at the specified index.
     *
     * If the index is invalid, nothing happens. If removing the frame
     * leaves the sprite empty, a new default blank frame is created.
     *
     * @param index The index of the frame to remove.
     */
    void removeFrame(int index);

    /**
     * @brief Duplicates a frame at the given index.
     *
     * @param index The index of the frame to duplicate.
     */
    void duplicateFrame(int index);

    /**
     * @brief Moves a frame from one index to another.
     *
     * If either index is invalid or both indices are the same, nothing happens.
     *
     * @param fromIndex The original index of the frame.
     * @param toIndex The new index for the frame.
     */
    void moveFrame(int fromIndex, int toIndex);

    /**
     * @brief Gets the current frame of the sprite.
     *
     * @return A reference to the current frame.
     */
    Frame& getCurrentFrame();

    /**
     * @brief Gets the current frame index.
     *
     * @return The index of the current frame.
     */
    int getCurrentFrameIndex() const;

    /**
     * @brief Gets a frame at the specified index.
     *
     * @param index The index of the frame to retrieve.
     * @return A reference to the frame at the given index.
     */
    Frame& getFrame(int index);

    /**
     * @brief Gets the playback frames per second.
     *
     * @return The FPS value.
     */
    int getFPS() const;

    /**
     * @brief Sets the playback speed of the sprite.
     *
     * @param fps The frames per second value.
     */
    void setFPS(int fps);

    /**
     * @brief Gets the total frame count.
     *
     * @return The number of frames.
     */
    int getFrameCount() const;

private:
    // Ordered list of frames that make up the sprite animation.
    std::vector<Frame> frames;
    // Playback speed for the animation preview in frames per second.
    int fps;
    // Index of the currently selected frame.
    int currentFrameIndex;

    static const int DEFAULT_WIDTH = 16;
    static const int DEFAULT_HEIGHT = 16;
    static const int DEFAULT_FPS = 12;

    /**
     * @brief Checks whether an index is valid for the frames vector.
     *
     * @param index The index to check.
     * @return True if the index is within bounds, false otherwise.
     */
    bool isValidIndex(int index) const;

    /**
     * @brief Creates a default blank frame for the sprite.
     *
     * The default frame uses the standard sprite width and height.
     *
     * @return A blank Frame object with the default resolution.
     */
    Frame makeDefaultFrame() const;
};

#endif // SPRITE_H
