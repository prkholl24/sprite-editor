/**
 * @file canvas.h
 * @brief Declares the Canvas class used as the drawing surface for the sprite editor.
 *
 * This file defines the Canvas widget, which is responsible for rendering the
 * current sprite frame and capturing user input. The Canvas follows the Model-View
 * design by acting as part of the view layer, it does not modify the model directly,
 * but instead communicates with the Controller using Qt signals and slots.
 *
 * Team: Green Goombas
 * github url: https://github.com/UofU-CS3505/cs3505-assignment8-GreenGoombas.git
 * @authors Charles Adair, Armando Carrillo, Parker Hollingsed,
 *          Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3/30/2026
 *
 * Last Revision: 3/30/2026 8:52AM MST by Lindsey Reese
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <vector>

namespace Ui {
class Canvas;
}

/**
 * @brief Provides the drawing area for the current sprite frame.
 *
 * The Canvas is responsible for rendering the current frame and displaying
 * pixel updates received from the Controller. It also captures user input
 * from the drawing surface.
 *
 * The Canvas does not modify the model directly. Instead, it communicates
 * user actions to the Controller through signals and receives pixel updates
 * from the Controller through slots.
 */
class Canvas : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a Canvas widget.
     *
     * Creates the canvas view and prepares it for rendering sprite data.
     *
     * @param parent The parent widget.
     */
    explicit Canvas(QWidget *parent = nullptr);

    /**
     * @brief Destroys for the Canvas widget.
     */
    ~Canvas();

public slots:
    /**
     * @brief Updates the displayed color of a single sprite pixel.
     *
     * This slot receives pixel data from the Controller and updates the
     * internal image used for rendering the sprite.
     *
     * @param x The x coordinate on the sprite grid, where 0 is the leftmost pixel.
     * @param y The y coordinate on the sprite grid, where 0 is the topmost pixel.
     * @param color A 4-element vector representing RGBA values {R, G, B, A}.
     */
    void drawPixel(int x, int y, std::vector<int> color);

    /**
     * @brief Initializes the canvas using the sprite dimensions.
     *
     * Sets the logical width and height of the sprite so the canvas knows
     * how many sprite pixels to render.
     *
     * @param width The width of the sprite in pixels.
     * @param height The height of the sprite in pixels.
     */
    void initialize(int width, int height);

signals:
    /**
     * @brief Emits the sprite coordinate selected by the user.
     *
     * This signal is sent when the user clicks or drags on the canvas so the
     * Controller can apply the currently selected tool at that location.
     *
     * @param x The x coordinate on the sprite grid, where 0 is the leftmost pixel.
     * @param y The y coordinate on the sprite grid, where 0 is the topmost pixel.
     */
    void canvasInputSignal(int x, int y);

protected:
    /**
     * @brief Draws the current sprite frame to the widget.
     *
     * Overrides QWidget's paintEvent to render the canvas contents to the screen.
     *
     * @param event Details about the paint event.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Handles an initial mouse press on the canvas.
     *
     * Converts the mouse position from widget coordinates to sprite coordinates
     * and emits canvasInputSignal for the selected pixel.
     *
     * @param event Details about the mouse press event.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Handles mouse movement while drawing on the canvas.
     *
     * If the user is dragging with the mouse pressed, this converts the current
     * mouse position to sprite coordinates and emits canvasInputSignal.
     *
     * @param event Details about the mouse move event.
     */
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::Canvas *ui;

    /**
     * @brief Stores the image currently being rendered on the canvas.
     */
    QImage render;

    /**
     * @brief Stores the number of pixel columns in the sprite.
     */
    int spriteWidth;

    /**
     * @brief Stores the number of pixel rows in the sprite.
     */
    int spriteHeight;

    /**
     * @brief Converts widget coordinates into sprite coordinates.
     *
     * Helper method used to map a mouse position on the widget to the
     * corresponding pixel location in the logical sprite grid.
     *
     * @param pos The position in widget coordinates.
     * @return The corresponding point in sprite coordinates.
     */
    QPoint mapToSprite(const QPoint &pos) const;
};

#endif // CANVAS_H
