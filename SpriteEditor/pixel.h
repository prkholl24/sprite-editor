/**
 * @file pixel.h
 *
 * @brief Declaration of the Pixel class used in the sprite editor.
 *
 * The Pixel class represents a single pixel within a frame. It stores
 * color information using RGBA values and provides methods to access
 * and modify those values. This class is part of the model layer and
 * is used by the Frame class to represent image data.
 *
 * @authors:
 * @date last modified:
 */

#ifndef PIXEL_H
#define PIXEL_H

#include <QObject>
#include <vector>

class Pixel : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Default constructor for Pixel.
     *
     * Initializes a Pixel object with no color set.
     *
     * @param parent Optional QObject parent.
     */
    explicit Pixel(QObject *parent = nullptr);

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
    //Color expressed as 4 int values
    //Red, Green, Blue, Alpha (Gamma/Opacity)
    std::vector<int> color;


signals:
};

#endif // PIXEL_H
