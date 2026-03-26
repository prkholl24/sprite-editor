#ifndef SPRITE_H
#define SPRITE_H

#include "frame.h"
#include <QObject>

/**
 * @brief Represents an animated sprite composed of multiple frames.
 *
 *This class manages a collection of frames and playback settings.
 */
class Sprite {
private:


    std::vector<Frame> frames;

    int fps;

    int currentFrame;

public:
    // explicit Sprite(QObject *parent = nullptr);

    // Frame getCurrentFrame();

    // void setFPS(int fps);

    // int getFrameCount();

    // void swapFrame();
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
     * @brief sets frames per second
     * @param fps New FPS value
     */
    int getFPS() const;

    /**
     * @brief gets total frame count.
     * @return number of frames
     */
    int getFrameCount() const;
};

#endif // SPRITE_H
