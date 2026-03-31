/**
 * @file pixel.h
 * @brief Declaration of the Pixel class
 *
 * This class represents a Pixel which contains color data
 *
 * Team: Green Goombas
 * github url: https://github.com/UofU-CS3505/cs3505-assignment8-GreenGoombas.git
 * @authors Charles Adair, Armando Carrillo, Parker Hollingsed,
 *          Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3/26/2026
 *
 * Last Revision: 3/30/2026 9:10PM MST by Lindsey Reese
 */

#ifndef PIXEL_H
#define PIXEL_H

#include <vector>
#include <QJsonObject>
#include <QJsonArray>

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
    Pixel(const std::vector<int>& color);

    /**
     * @brief Copy constructor for Pixel.
     *
     * Creates a new Pixel as a copy of another Pixel.
     *
     * @param px The Pixel to copy.
     */
    Pixel(const Pixel& px);

    /**
     * @brief Assignment operator for Pixel.
     *
     * Assigns the color values from another Pixel to this Pixel.
     *
     * @param px The Pixel to copy from.
     * @return A reference to this Pixel.
     */
    Pixel& operator=(const Pixel& px);


    /**
     * @brief Converts Pixel object into Pixel QJsonObject for serializing into .ssp
     * @return Pixel QJsonObject
     */
    QJsonObject toJson() const;

    /**
     * @brief Converts Pixel QJsonObject into Pixel Object for deserializing.
     * @param Pixel Json
     * @return Pixel
     */
    static Pixel fromJson(const QJsonObject &json);

    /**
     * @brief Gets the color of the Pixel.
     *
     * Returns the RGBA color values stored in this Pixel.
     *
     * @return A vector of integers representing RGBA values.
     */
    std::vector<int> getColor() const;

    /**
     * @brief Sets the color of the Pixel.
     *
     * Updates the Pixel’s RGBA color values if the input is valid.
     * Vector must be length 4 and all values must be between 0-255.
     *
     * @param newColor A vector of integers representing RGBA values.
     */
    void setColor(const std::vector<int>& newColor);

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
