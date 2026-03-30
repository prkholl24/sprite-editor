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
 * @brief The Canvas class provides a drawing area for the current frame being edited.
 *
 * The canvas only handles user inputs and renders pixels.
 * Both of these functionalities are dependent on the Controller.
 */
class Canvas : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a Canvas.
     * @param parent widget
     */
    explicit Canvas(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Canvas widget.
     */
    ~Canvas();

public slots:
    /**
     * @brief Receives pixel data from the Controller to update the rendering.
     * @param x is the x-coordinate on the sprite grid where 0 is the left most pixel.
     * @param y is the y-coordinate on the sprite grid where 0 is the top most pixel.
     * @param color A 4-element vector representing RGBA values [R, G, B, A].
     *
     * This slot is intended to be connected to the Controller's drawPixel signal.
     * It updates the internal visual cache at the specified coordinates and
     * schedules a redraw of the widget.
     */
    void drawPixel(int x, int y, std::vector<int> color);

    /**
     * @brief Initializes the canvas with sprite dimensions.
     * @param width The width of the sprite in pixels.
     * @param height The height of the sprite in pixels.
     *
     * This slot decides how many pixels should be rendered and how big to make them.
     */
    void initialize(int width, int height);

signals:
    /**
     * @brief Notifies the Controller of user input at specific coordinates.
     * @param x is the x-coordinate on the sprite grid where 0 is the left most pixel.
     * @param y is the y-coordinate on the sprite grid where 0 is the top most pixel.
     *
     * Signal emitted when left click is clicked, or continuously if left click is held.
     */
    void canvasInputSignal(int x, int y);

protected:
    /**
     * @brief Renders the visual state of the sprite to the screen.
     * @param event Details of the paint event.
     *
     * Override of a method in QWidget. Handles what to draw and how.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Captures the initial mouse interaction.
     * @param event Details of the mouse press event.
     *
     * Overrides the standard mouse press event to map screen coordinates
     * to logical sprite coordinates and emit the canvasInputSignal.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Captures continuous mouse movement for drawing/selection.
     * @param event Details of the mouse move event.
     *
     * Overrides the standard mouse move event. If the mouse is being dragged,
     * it maps screen coordinates to logical sprite coordinates and emits
     * the canvasInputSignal.
     */
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::Canvas *ui;
    /**
     * @brief render stores the data for what is currently being displayed
     */
    QImage render;
    /**
     * @brief spriteWidth is the number of pixel columns to create
     */
    int spriteWidth;
    /**
     * @brief spriteHeight is the number of pixel rows to create
     */
    int spriteHeight;

    /**
     * @brief Maps a widget-space coordinate to a logical sprite coordinate.
     * @param pos The position in widget coordinates (pixels).
     * @return The corresponding (x, y) point in sprite coordinates.
     *
     * Helper method to convert the local position of a mouse event into
     * the corresponding (x, y) index on the sprite grid based on the widget's
     * current scaling.
     */
    QPoint mapToSprite(const QPoint &pos) const;
};

#endif // CANVAS_H
