/**
 * @file frame.h
 * @brief Declaration of the Frame class.
 *
 * This class manages a 2D array of Pixel objects which represents a still image.
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/26/2026 3:01PM MST by Charles Adair
 */

#ifndef FRAME_H

#define FRAME_H

#include "pixel.h"

/**
 * @brief The Frame class represents a two dimensional array of pixels.
 *
 * This supports
 */

class Frame
{
public:
    /**
     * @brief Frame constructor
     *
     * @param x the width of the frame
     * @param y the height of the frame
     */
    explicit Frame(int x = 16, int y = 16 );

    /**
     * @brief getPixel of the location specified.
     *
     * @param x value where 0 is the left-most column.
     * @param y value where 0 is the top-most row.
     * @return the Pixel object located at the x and y specified
     */
    Pixel& getPixel(int x, int y);

    /**
     * @brief Gets the width of the frame.
     * @return frame width
     */
    int getWidth() const;

    /**
     * @brief Gets the height of the frame.
     * @return frame height
     */
    int getHeight() const;

private:
    /**
     * @brief width of the frame
     */
    int width;

    /**
     * @brief height of the frame
     */
    int height;

    /**
     * @brief pixels is two dimensional vector containing all of the color data through Pixel objects.
     */
    std::vector<std::vector<Pixel>> pixels;
};

#endif // FRAME_H
