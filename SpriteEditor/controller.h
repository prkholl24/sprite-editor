#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "frame.h"
#include "qpixmap.h"
#include <QObject>
#include <QWidget>
#include <QTimer>
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
     * @brief Creates and returns the Art Deco color palette.
     *
     * This palette is inspired by Pantone color selections featured in
     * "Pantone: The 20th Century in Color", representing the Art Deco
     * design movement of the 1920s. The palette emphasizes luxury,
     * contrast, and refined materials, including metallic tones,
     * neutrals, and bold accents commonly used in architecture,
     * fashion, and interior design of the era.
     *
     * The colors are based on Pantone references including Lavender Violet,
     * Turtledove, Champagne Beige, Carnelian, Jet Black, and Silver.
     *
     * The palette is represented as a 3x2 Frame where each pixel corresponds
     * to a selectable color in the UI.
     *
     * Layout (x, y):
     * (0,0) Lavender Violet   (1,0) Turtledove        (2,0) Champagne Beige
     * (0,1) Carnelian         (1,1) Jet Black         (2,1) Silver
     *
     * Each color is stored as an RGBA vector in the format:
     * {red, green, blue, alpha}, where alpha = 255 (fully opaque).
     *
     * @return A pointer to Frame containing the palette colors.
     */
    Frame* artDecoPalette();

    /**
     * @brief Creates and returns the Retro Pastel color palette.
     *
     * This palette is inspired by Pantone color selections featured in
     * "Pantone: The 20th Century in Color", representing softer color trends
     * of the 1960s seen in fashion, film, and advertising. The palette emphasizes
     * light, pastel tones commonly associated with elegance, femininity,
     * and mid-century design aesthetics.
     *
     * The palette is represented as a 3x2 Frame where each pixel corresponds
     * to a selectable color in the UI.
     *
     * Layout (x, y):
     * (0,0) Blush Pink (9286)   (1,0) Mint (5483)       (2,0) Pale Yellow (9140)
     * (0,1) Baby Blue (9402)    (1,1) Peach (9200)      (2,1) Lavender (9340)
     *
     * Each color is stored as an RGBA vector in the format:
     * {red, green, blue, alpha}, where alpha = 255 (fully opaque).
     *
     * @return A pointer to Frame containing the palette colors.
     */
    Frame* retroPastelPalette();

    /**
     * @brief Creates and returns the Sixties Pop color palette.
     *
     * This palette is inspired by Pantone color selections featured in
     * "Pantone: The 20th Century in Color", particularly the pop art
     * movement of the 1960s as shown in work by artists like Andy Warhol.
     * The palette emphasizes bold, high-contrast colors and playful,
     * graphic combinations commonly used in pop art prints and media.
     *
     * The palette is represented as a 3x3 Frame where each pixel corresponds
     * to a selectable color in the UI.
     *
     * Layout (x, y):
     * (0,0) Red (7621)        (1,0) Orange (158)      (2,0) Teal (7713)
     * (0,1) Green (340)       (1,1) Light Aqua (318)  (2,1) Pink (516)
     * (0,2) Purple (7662)     (1,2) Lime (7744)       (2,2) Yellow (1235)
     *
     * Each color is stored as an RGBA vector in the format:
     * {red, green, blue, alpha}, where alpha = 255 (fully opaque).
     *
     * @return A pointer to Frame containing the palette colors.
     */
    Frame* sixtiesPopPalette();

    /**
     * @brief Creates and returns the Seventies Earth color palette.
     *
     * This palette is inspired by Pantone color selections featured in
     * "Pantone: The 20th Century in Color", specifically the
     * "Avocado and Harvest Gold" section representing 1970s interior
     * and design trends. The palette emphasizes earthy, muted tones
     * commonly used in 1970s home decor, textiles, and appliances.
     *
     * The colors are based on Pantone references including Avocado,
     * Golden Olive, Cream Gold, Harvest Gold, Burnt Orange, and
     * Tortoise Shell.
     *
     * The palette is represented as a 3x2 Frame where each pixel corresponds
     * to a selectable color in the UI.
     *
     * Layout (x, y):
     * (0,0) Avocado        (1,0) Golden Olive     (2,0) Cream Gold
     * (0,1) Harvest Gold   (1,1) Burnt Orange     (2,1) Tortoise Shell
     *
     * Each color is stored as an RGBA vector in the format:
     * {red, green, blue, alpha}, where alpha = 255 (fully opaque).
     *
     * @return A pointer to Frame containing the palette colors.
    */
    Frame* seventiesEarthPalette();

    /**
     * @brief Creates and returns the Eighties Neon color palette.
     *
     * This palette is inspired by Pantone color selections featured in
     * "Pantone: The 20th Century in Color", specifically the "The Day the
     *  Word Turned Day-Glo” section, featuring aesthetic associated with
     *  1980s fashion and design. The palette emphasizes high-saturation,
     *  fluorescent colors commonly used in punk, pop, and experimental
     *  visual styles of the era.
     *
     * The colors are based on Pantone references including Process Blue,
     * 7488 (green), Yellow 012, 1575, Orange 021, 213, Rhodamine Red,
     * and Black 6.
     *
     * The palette is represented as a 3x3 Frame where each pixel corresponds
     * to a selectable color in the UI.
     *
     * Layout (x, y):
     * (0,0) Process Blue        (1,0) Pantone 7488 Green   (2,0) Yellow 012
     * (0,1) Pantone 1575        (1,1) Orange 021           (2,1) Pantone 213 Pink
     * (0,2) Rhodamine Red       (1,2) Black 6              (2,2) White (neutral)
     *
     * Each color is stored as an RGBA vector in the format:
     * {red, green, blue, alpha}, where alpha = 255 (fully opaque).
     *
     * @return A pointer to Frame containing the palette colors.
     */
    Frame* eightiesNeonPalette();

    /**
     * @brief Timer used to trigger the animation playback for the preview window.
     */
    QTimer* previewTimer = nullptr;

    /**
     * @brief Stores the index of the frame currently being displayed in the preview.
     */
    int previewFrameIndex = 0;
    /**
     * @brief Helper method to initialize the preview timer and its connections.
     */
    void initializePreviewTimer();

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

    /**
     * @brief drawPreviewPixel
     * @param x coordinate
     * @param y coordinate
     * @param color in [R,G,B,A] format
     *
     * Singal connects to the preview widget.
     * Triggers continuously to display the animation.
     */
    void drawPreviewPixel(int x, int y, std::vector<int> color);
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
     * @brief Sets the sprite's framerate accordingly upon reception of an fpsChanged() signal.
     * @param fps The FPS value to set.
     */
    void setSpriteFPS(int fps);

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

    void handleAddFrame();
    void handleRemoveFrame(int index);
    void handleFrameSelected(int index);
    void handleFpsChanged(int fps);

    /**
     * @brief Advances the preview animation to the next frame.
     *
     * Triggered by previewTimer.
     */
    void updatePreview();

    void newProjectSlot(int spriteSize);

    /**
     * @brief handleCanvasInputSlot
     * @param x
     * @param y
     */
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
