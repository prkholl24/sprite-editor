/**
 * @file frame.h
 * @brief Declares the Frame class used to store a 2D grid of pixels.
 *
 * The Frame class represents a single still image in the sprite editor.
 * It manages a 2D vector of Pixel objects and provides access to individual
 * pixels as well as the overall dimensions of the frame.
 *
 * Team: Green Goombas
 * GitHub: https://github.com/UofU-CS3505/cs3505-assignment8-GreenGoombas.git
 * @authors Charles Adair, Armando Carrillo, Brady Nelson,
 *          Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/30/2026 9:00PM MST by Lindsey Reese
 */

#ifndef FRAME_H
#define FRAME_H

#include "pixel.h"

/**
 * @brief Represents a 2D grid of pixels for a single frame.
 *
 * The Frame stores pixel color data in a two-dimensional vector and provides
 * methods to access and query pixel values. It acts as part of the model layer
 * and does not handle rendering or user input.
 */
class Frame
{
public:
    /**
     * @brief Constructs a Frame with the given dimensions.
     *
     * Initializes a 2D grid of Pixel objects with the specified width and height.
     * Default size is 16x16.
     *
     * @param x The width of the frame (number of columns).
     * @param y The height of the frame (number of rows).
     */
    explicit Frame(int x = 16, int y = 16 );

    /**
     * @brief Returns a reference to the pixel at the given coordinates.
     *
     * Allows direct access and modification of a pixel in the frame.
     *
     * @param x The x coordinate (column), where 0 is the leftmost column.
     * @param y The y coordinate (row), where 0 is the topmost row.
     * @return A reference to the Pixel at (x, y).
     */
    Pixel& getPixel(int x, int y);

    /**
     * @brief Gets the width of the frame.
     * @return The number of columns in the frame.
     */
    int getWidth() const;

    /**
     * @brief Gets the height of the frame.
     * @return The number of rows in the frame.
     */
    int getHeight() const;

    /**
     * @brief Stores all pixel data in a 2D vector.
     *
     * Indexed as pixels[x][y], where x is the column and y is the row.
     */
    std::vector<std::vector<Pixel>> pixels;

private:
    /**
     * @brief The width of the frame (number of columns).
     */
    int width;

    /**
     * @brief The height of the frame (number of rows).
     */
    int height;

};

#endif // FRAME_H
