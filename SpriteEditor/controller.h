#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "frame.h"
#include "qpixmap.h"
#include <QObject>
#include <QWidget>
#include <vector>
#include "sprite.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief model is the current Sprite object being edited
     *
     * Model object starts uninitialized.
     */
    Sprite* model = nullptr;

    Frame* currentFrame = nullptr;

    /**
     * @brief Index of the currently selected frame in the sprite.
     */
    int currentFrameIndex = 0;

    std::vector<int> currentColor = {0, 0, 0, 255}; // Default black (RGBA)

    enum class ToolStates {StandardBrush, PaintBucket, Eraser, Eyedropper, Mirror, SelectionTool};

    ToolStates currentTool = ToolStates::StandardBrush;
    
    void fillBucket();

    /**
     * @brief Loops through the current frame and emits drawPixel for every pixel.
     * Ensures the Canvas View is perfectly synced with the Model.
     */
    void updateCanvas();
public:
    /**
     * @brief Controller constructor
     *
     * Creates a new controller object with no model initialized.
     * On initialization this Controller waits for a signal from the
     * "New" or "Load" buttons in order to create the Sprite object
     * to manipulate
     */
    Controller(QWidget *parent = nullptr);
signals:
    void frameModified();
    // sends the pixmap over to the view.
    void sendPixmap(int index, QPixmap map);
    // sends specific pixel data to the canvas.
    void drawPixel(int x, int y, std::vector<int> color);

    // tells the canvas to resize its internal buffers.
    void initializeCanvas(int width, int height);

    // tells the timeline to sync its frame count with the model.
    void setTimelineFrameCount(int count);

public slots:
    /**
     * @brief Receives a frame from the Model, and converts it to a pix map.
     * Does this via "emit sendPixmap(pixmap-you-just-made)".
     * @param index The index of the frame button to update
     * @param frame The frame to convert
     */
    void convertToPixmap(int index, Frame frame);

    /**
     * @brief Converts all frames to pixmaps and sends them to the timeline.
     * Use this when loading a new sprite or initializing the timeline.
     * @param frames Vector of all frames to convert
     */
    void convertAllFrames(const std::vector<Frame>& frames);

    /**
     * @brief standardBrush
     *
     * Paints one pixel in Sprite.
     * @param x and y coordinate
     */
    void standardBrush(int x, int y);

    /**
     * @brief eraserBrush
     *
     * Erases one pixel in Sprite.
     * @param x and y coordinate
     */
    void eraserTool(int x, int y);

    /**
     * @brief fillBucket
     *
     * Fills a enclosed area with one color.
     * @param x and y coordinate
     */
    void fillBucket(int x, int y);

    /**
     * @brief fillBucketLogic
     *
     * Depth-First Search fill bucket helper method.
     * FLOOD FILL ALGORITHM
     * TODO: UNTESTED UNTIL CANVAS IS DONE
     */
    void fillBucketLogic(std::vector<std::vector<Pixel>>& pixelGrid, int x, int y, std::vector<int> oldColor);

    /**
     * @brief eyeDropperTool
     *
     * Saves selected color of selected pixel.
     * @param x and y coordinate
     */
    void eyeDropperTool(int x, int y);

    /**
     * @brief mirrorTool
     *
     * Mirror sprite manipulation.
     * @param x and y coordinate
     */
    void mirrorTool(int x, int y);

    /**
     * @brief selectionTool
     *
     * Selects pixel selection tool.
     * @param x and y coordinate
     */
    void selectionTool(int x, int y);

public slots:
    void newProjectSlot(int spriteSize);
    void handleCanvasInputSlot(int x, int y);

    /// TIMELINE SLOTS ///
    /**
     * @brief Switches to the frame at the given index.
     * Updates currentFrame and currentFrameIndex, then refreshes the canvas.
     * @param index The index of the frame to select.
     */
    void frameSelectedSlot(int index);

    /**
     * @brief Adds a new frame to the model at the given index.
     * @param index The index where the frame was added in the timeline.
     */
    void addFrameSlot(int index);

    /**
     * @brief Removes the frame at the given index from the model.
     * @param index The index of the frame to remove.
     */
    void removeFrameSlot(int index);

    /**
     * @brief Sets the FPS (frames per second) in the model.
     * @param fps The new FPS value.
     */
    void setSpriteFPS(int fps);

    /// TOOL BAR ///
    void standardBrushSelectedSlot();
    void eraserToolSelectedSlot();
    void paintBucketSelectedSlot();
    void eyeDropperToolSelectedSlot();
    void mirrorToolSelectedSlot();
    void selectionToolSelectedSlot();

};

#endif // CONTROLLER_H
