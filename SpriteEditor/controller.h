#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "frame.h"
#include "qpixmap.h"
#include <QObject>
#include <QWidget>
#include <vector>
#include "sprite.h"
#include "palettedata.h"

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

    std::vector<int> currentColor = {0, 0, 0, 255}; // Default black (RGBA)

    enum class ToolStates {StandardBrush, PaintBucket, Eraser, Eyedropper, Mirror, SelectionTool};

    ToolStates currentTool = ToolStates::StandardBrush;
    
    void fillBucket();

    /**
     * @brief Loops through the current frame and emits drawPixel for every pixel.
     * Ensures the Canvas View is perfectly synced with the Model.
     */
    void updateCanvas();

    /**
     * @brief colorPalette contains a set of colors to choose from.
     *
     * Renders to a Canvas widget.
     */
    Frame* colorPalette = nullptr;

    PaletteType selectedPalette = PaletteType::Default;

    /**
     * @brief updateColorPalette
     *
     * Handles drawing to the color palette.
     */
    void updateColorPalette();

    /**
     * @brief defaultPalette
     * @return
     *
     * Creates the default color wheel
     */
    Frame* defaultPalette();

    /**
     * @brief artDecoPalette
     * @return
     */
    Frame* artDecoPalette();

    /**
     * @brief retroPastelPalette
     * @return
     */
    Frame* retroPastelPalette();

    /**
     * @brief sixtiesPopPalette
     * @return
     */
    Frame* sixtiesPopPalette();

    /**
     * @brief seventiesEarthPalette
     * @return
     */
    Frame* seventiesEarthPalette();

    /**
     * @brief eightiesNeonPalette
     * @return
     */
    Frame* eightiesNeonPalette();

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

    /**
     * @brief drawPixel to the Canvas
     * @param x coordinate
     * @param y coordinate
     * @param color in [R,G,B,A] format
     *
     * Singal connects to the canvas widget to update to reflect
     * changes to `model`.
     */
    void drawPixel(int x, int y, std::vector<int> color);

    /**
     * @brief initializeCanvas
     * @param width in pixels
     * @param height in pixels
     *
     * Tells the canvas how many pixels it needs to render.
     */
    void initializeCanvas(int width, int height);

    /**
     * @brief initializeColorPalette
     * @param width in pixels
     * @param height in pixels
     *
     * Tells the color palette how many pixels it needs to render
     */
    void initializeColorPalette(int width, int height);

    /**
     * @brief drawColorPalettePixel
     * @param x coordinate
     * @param y coordinate
     * @param color in [R,G,B,A] format
     *
     * Singal connects to the color palette widget.
     * Triggers update to reflect changes to `colorPalette`.
     */
    void drawColorPalettePixel(int x, int y, std::vector<int> color);

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

    /**
     * @brief initializePalette creates the color palette
     * @param size effects the number of colors which are created
     *
     * Creates a new Frame object and populates it with colors.
     * Colors a
     */
    void initializePalette();

    void newProjectSlot(int spriteSize);

    /**
     * @brief handleCanvasInputSlot
     * @param x
     * @param y
     */
    void handleCanvasInputSlot(int x, int y);

    /// TOOL BAR ///
    void standardBrushSelectedSlot();
    void eraserToolSelectedSlot();
    void paintBucketSelectedSlot();
    void eyeDropperToolSelectedSlot();
    void mirrorToolSelectedSlot();
    void selectionToolSelectedSlot();

    /**
     * @brief handleColorPaletteInput
     * @param x coordinate
     * @param y coordinate
     *
     * Interprets a color palette input and sets the pixel color at some
     * coordinate to the currentColor
     */
    void handleColorPaletteInput(int x, int y);

    /**
     * @brief Slot handles behavior for when the color wheel palette is selected.
     */
    void defaultPaletteSelected();

    /**
    * @brief Slot handles behavior for when the art deco palette is selected.
     */
    void artDecoPaletteSelected();

    /**
    * @brief Slot handles behavior for when the retro palette is selected.
     */
    void retroPastelPaletteSelected();

    /**
    * @brief Slot handles behavior for when the sixties pop palette is selected.
     */
    void sixtiesPopPaletteSelected();

    /**
     * @brief Slot handles behavior for when the earth palette is selected.
     */
    void seventiesEarthPaletteSelected();

    /**
     * @brief Slot handles behavior for when the eighties palette is selected.
     */
    void eightiesNeonPaletteSelected();

};

#endif // CONTROLLER_H
