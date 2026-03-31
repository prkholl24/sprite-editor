/**
 * @file sprite.h
 * @brief Declaration of the Sprite class.
 *
 * This class manages a collection of Frame objects and controls animation
 * behavior such as frame order and frames per second.
 * It also tracks the currently active frame.
 *
 * Team: Green Goombas
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/27/2026 1:26AM MST by Charles Adair
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
class Sprite {
private:


    /**
     * @brief Frame rate at which the playback occurs
     */
    int fps;

    /**
     * @brief width of the Sprite animation
     */
    int width;

    /**
     * @brief height of the Sprite animation
     */
    int height;


    /**
     * @brief Default values for a new Sprite object
     */
    static const int DEFAULT_WIDTH = 16;
    static const int DEFAULT_HEIGHT = 16;
    static const int DEFAULT_FPS = 12;

    /**
     * @brief Checks whether an index is valid for the frames vector.
     *
     * @param index The index to check.
     * @return True if the index is within bounds, false otherwise.
     */
    bool isValidFrameIndex(int index) const;

    /**
     * @brief Creates a default blank frame for the sprite.
     *
     * The default frame uses the standard sprite width and height.
     *
     * @return A blank Frame object with the default resolution.
     */
    Frame createDefaultFrame() const;

public:

    /**
     * @brief Frames is  a set of 2D arrays containing color data ordered by
     * the sequence in which they are played back.
     */
    std::vector<Frame> frames;

    /**
     * @brief Default constructor for Sprite.
     *
     * Initializes a sprite with one default frame, a default FPS value,
     * and the current frame index set to 0.
     */
    Sprite();

    /**
     * @brief Sprite constructor accepts parameters for resolution.
     * @param Width in pixels
     * @param Height in pixel.
     */
    Sprite(int width, int height);

    /**
     * @brief Adds a new frame to the sprite.
     *
     * Appends a frame to the list of frames in the sprite.
     *
     * @param frame The frame to add.
     */
    void addFrame();

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
     * @brief Sets a new playback speed
     * @param newFPS The new speed measured in Frames Per Second (FPS).
     */
    void setFPS(int newFPS);

    /**
     * @brief Gets the width of the sprite.
     * @return sprite width
     */
    int getWidth() const;

    /**
     * @brief Gets the height of the sprite.
     * @return sprite height
     */
    int getHeight() const;

    /**
     * @brief Gets the total frame count.
     *
     * @return The number of frames.
     */
    int getFrameCount() const;

    /**
     * @brief Converts Sprite object into Sprite QJsonObject for serializing into .ssp
     * @return Sprite QJsonObject
     */
    QJsonObject toJson() const;

    /**
     * @brief Converts Sprite QJsonObject into Sprite object pointer for deserializing.
     * @param Sprite QJsonObject
     * @return Sprite object pointer
     */
    static Sprite* fromJson(const QJsonObject &json);
};

#endif // SPRITE_H
