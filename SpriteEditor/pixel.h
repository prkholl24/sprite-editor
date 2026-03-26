/**
 * @file pixel.h
 * @brief Declaration of the Pixel class
 *
 * This class represents a Pixel which contains color data
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/26/2026 3:02PM MST by Charles Adair
 */

#ifndef PIXEL_H
#define PIXEL_H

#include <vector>

class Pixel
{
public:

    /**
     * @brief Default constructor for Pixel.
     *
     * Initializes a Pixel object with no color set.
     */
    Pixel();

    /**
     * @brief Constructs a Pixel with a specified color.
     *
     * Initializes the Pixel with the given RGBA color values.
     *
     * @param color A vector of integers representing RGBA values.
     */
    Pixel(std::vector<int>& color);

    /**
     * @brief Copy constructor for Pixel.
     *
     * Creates a new Pixel as a copy of another Pixel.
     *
     * @param px The Pixel to copy.
     */
    Pixel(Pixel& px);

    /**
     * @brief Assignment operator for Pixel.
     *
     * Assigns the color values from another Pixel to this Pixel.
     *
     * @param px The Pixel to copy from.
     */
    void operator=(Pixel& px);

    /**
     * @brief Gets the color of the Pixel.
     *
     * Returns the RGBA color values stored in this Pixel.
     *
     * @return A reference to a vector of integers representing RGBA values.
     */
    std::vector<int> const getColor();

    /**
     * @brief Sets the color of the Pixel.
     *
     * Updates the Pixel’s RGBA color values.
     *
     * @param newColor A vector of integers representing RGBA values.
     */
    void setColor(std::vector<int>& newColor);

    /**
     * @brief Sets the opacity of the Pixel.
     *
     * Updates the alpha (opacity) channel of the Pixel’s color.
     *
     * @param opacity An integer representing the new opacity value.
     */
    void setOpacity(int opacity);

private:

    /**
     * @brief color expressed as 4 int values
     *
     * Red, Green, Blue, Alpha (Gamma/Opacity)
     */
    std::vector<int> color;
};

#endif // PIXEL_H
