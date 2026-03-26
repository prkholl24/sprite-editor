#ifndef FRAME_H

#define FRAME_H

#include <QObject>
#include "pixel.h"

/**
 * @brief The Frame class represents a two dimensional array of pixels.
 *
 * This supports
 */

class Frame : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief width is the maximum x value which can be retrieved or set.
     */
    int width;

    /**
     * @brief heightis the maximum y value which can be retrieved or set.
     */
    int height;

    /**
     * @brief Frame constructor
     *
     * @param parent the Sprite object which holds this Frame object.
     */
    explicit Frame(QObject *parent = nullptr);

    /**
     * @brief getPixel of the location specified.
     *
     * @param x value where 0 is the left-most column.
     * @param y value where 0 is the top-most row.
     * @return the Pixel object located at the x and y specified
     */
    std::vector<int> getPixelColor(int x, int y);

    /**
     * @brief setPixel
     *
     * @param x value where 0 is the left-most column.
     * @param y value where 0 is the top-most row..
     * @param color represented by a vector containing four integers in this order–red, green, blue, alpha (opacity).
     */
    void setPixelColor(int x, int y, std::vector<int> color);

    /**
     * @brief changeResolution changes the maximum allowed input values for set and get pixel and initializes the pixels.
     *
     * @param w – the new maxmium width.
     * @param h - the new maximum height.
     */
    void setResolution(int w, int h);

private:
    /**
     * @brief pixels is two dimensional vector containing all of the color data through Pixel objects.
     */
    std::vector<std::vector<Pixel>> pixels;

signals:
};

#endif // FRAME_H
