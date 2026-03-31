/**
 * @file controller.h
 * @brief Defines the Controller class for the sprite editor application.
 *
 * This file contains the declaration of the Controller class, which manages
 * communication between the Sprite model and the user interface. The Controller
 * handles user input from the view, updates the model, and emits signals to keep
 * the canvas, timeline, and color palette in sync.
 *
 * Team: Green Goombas
 * github url: https://github.com/UofU-CS3505/cs3505-assignment8-GreenGoombas.git
 * @authors Charles Adair, Armando Carrillo, Parker Hollingsed,
 *          Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3/30/2026
 *
 * Last Revision: 3/30/2026 8:52PM MST by Lindsey Reese
 */

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
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileDialog>

/**
 * @brief Coordinates interactions between the model and the UI.
 *
 * The Controller responds to user actions (mouse input, toolbar selection,
 * palette selection), applies changes to the Sprite model, and emits signals
 * so the view updates accordingly. It also manages tool state and the active
 * color palette.
 */
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

    /**
     * @brief Points to the frame currently being edited.
     */
    Frame* currentFrame = nullptr;

    /*
     * @brief Index of the currently selected frame in the sprite.
     */
    int currentFrameIndex = 0;

    /**
     * @brief Stores the currently selected drawing color in RGBA format.
     *
     * Default color is black (RGBA).
     */
    std::vector<int> currentColor = {0, 0, 0, 255}; // Default black (RGBA)

    enum class ToolStates {StandardBrush, PaintBucket, Eraser, Eyedropper, Mirror, SelectionTool};

    ToolStates currentTool = ToolStates::StandardBrush;

    void fillBucket();

    /**
     * @brief Loops through the current frame and emits drawPixel for every pixel.
     *
     * Ensures the Canvas View is perfectly synced with the Model.
     */
    void updateCanvas();

    /**
     * @brief colorPalette contains a set of colors to choose from.
     *
     * Renders to a Canvas widget.
     */
    Frame* colorPalette = nullptr;

    /**
     * @brief Stores which preset color palette is currently selected.
     */
    PaletteType selectedPalette = PaletteType::Default;

    /**
     * @brief Updates the color palette view to match the current palette.
     *
     * Emits initializeColorPalette and drawColorPalettePixel so the palette
     * widget redraws using the colors stored in colorPalette.
     */
    void updateColorPalette();

    /**
     * @brief Creates and returns the default color palette.
     *
     * This is the fallback palette used when no themed palette is selected.
     * It provides a standard color wheel so the user can choose from a wide
     * range of basic colors.
     *
     * @return A pointer to a Frame containing the default palette colors.
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
     *  Word Turned Day-Glo” section, featuring the aesthetic associated with
     *  1980s fashion and design. The palette emphasizes high-saturation,
     *  fluorescent colors commonly used in punk, pop, and experimental
     *  visual styles of the era.
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
     * @brief clearCanvas
     *
     * Tells the canvas to clear itself before redrawing.
     */
    void clearCanvas();

    /**
     * @brief drawPixel to the Canvas
     *
     * Signal connects to the canvas widget to update to reflect
     * changes to `model`.
     *
     * @param x coordinate
     * @param y coordinate
     * @param color in [R,G,B,A] format
     */
    void drawPixel(int x, int y, std::vector<int> color);

    /**
     * @brief initializeCanvas
     *
     * Tells the canvas how many pixels it needs to render.
     *
     * @param width in pixels
     * @param height in pixels
     */
    void initializeCanvas(int width, int height);

    /**
     * @brief initializeColorPalette
     *
     * Tells the color palette how many pixels it needs to render
     *
     * @param width in pixels
     * @param height in pixels
     */
    void initializeColorPalette(int width, int height);

    /**
     * @brief drawColorPalettePixel
     *
     * Signal connects to the color palette widget.
     * Triggers update to reflect changes to `colorPalette`.
     *
     * @param x coordinate
     * @param y coordinate
     * @param color in [R,G,B,A] format
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
     *
     * Does this via "emit sendPixmap(pixmap-you-just-made)".
     *
     * @param index The index of the frame button to update
     * @param frame The frame to convert
     */
    void convertToPixmap(int index, Frame frame);

    /**
     * @brief Converts all frames to pixmaps and sends them to the timeline.
     *
     * Use this when loading a new sprite or initializing the timeline.
     */
    void convertAllFrames();

    /**
     * @brief Paints a single pixel using the current drawing color.
     * @param fps The FPS value to set.
     */
    void setSpriteFPS(int fps);

    /**
     * @brief standardBrush
     *
     * Called when the standard brush tool is active. Sets the pixel at the
     * selected coordinate to currentColor and updates the canvas.
     *
     * @param x The x coordinate of the selected pixel.
     * @param y The y coordinate of the selected pixel.
     */
    void standardBrush(int x, int y);

    /**
     * @brief Erases a single pixel.
     *
     * Called when the eraser tool is active. Resets the pixel at the selected
     * coordinate to a default or transparent color and updates the canvas.
     *
     * @param x The x coordinate of the selected pixel.
     * @param y The y coordinate of the selected pixel.
     */
    void eraserTool(int x, int y);

    /**
     * @brief Fills a connected region starting at the selected pixel.
     *
     * Called when the paint bucket tool is active. Replaces all connected pixels
     * that match the starting pixel’s color with currentColor.
     *
     * @param x The x coordinate of the selected pixel.
     * @param y The y coordinate of the selected pixel.
     */
    void fillBucket(int x, int y);

    /**
     * @brief Recursive helper method for the paint bucket tool.
     *
     * Performs a depth-first flood fill on the pixel grid, replacing all connected
     * pixels that match oldColor with currentColor.
     *
     * @param pixelGrid The grid of pixels being modified.
     * @param x The current x coordinate being checked.
     * @param y The current y coordinate being checked.
     * @param oldColor The original color being replaced.
     */
    void fillBucketLogic(std::vector<std::vector<Pixel>>& pixelGrid, int x, int y, std::vector<int> oldColor);

    /**
     * @brief Samples the color at the selected coordinate.
     *
     * Called when the eyedropper tool is active. Sets currentColor to match
     * the color of the selected pixel.
     *
     * @param x The x coordinate of the selected pixel.
     * @param y The y coordinate of the selected pixel.
     */
    void eyeDropperTool(int x, int y);

    /**
     * @brief Draws a mirrored pixel across the canvas.
     *
     * Called when the mirror tool is active. Applies the same color to the
     * mirrored position of the selected pixel.
     *
     * @param x The x coordinate of the selected pixel.
     * @param y The y coordinate of the selected pixel.
     */
    void mirrorTool(int x, int y);

    /**
     * @brief Handles selection tool behavior.
     *
     * Called when the selection tool is active. Allows selecting regions or
     * pixels for future operations.
     *
     * @param x The x coordinate of the selected pixel.
     * @param y The y coordinate of the selected pixel.
     */
    void selectionTool(int x, int y);

public slots:
  
    void loadProjectSlot(QString filePath);
    void saveProjectSlot(QString filePath);


    /**
     * @brief Initializes the currently selected preset color palette.
     * @param size effects the number of colors which are created
     *
     * Deletes the existing palette (if one exists), creates a new palette
     * based on selectedPalette, and updates the palette view to reflect it.
     */
    void initializePalette();

    void handleAddFrame();
    void handleRemoveFrame(int index);
    void handleFrameSelected(int index);

    /**
     * @brief Advances the preview animation to the next frame.
     *
     * Triggered by previewTimer.
     */
    void updatePreview();

    /**
     * @brief Creates a new sprite project with the given size.
     *
     * Initializes a new Sprite model, sets the first frame as currentFrame,
     * resets the drawing color, and updates the canvas to reflect the new project.
     *
     * @param spriteSize The width and height of the new sprite in pixels.
     */
    void newProjectSlot(int spriteSize);

    /**
     * @brief Handles user input on the canvas.
     *
     * Applies the currently selected tool to the given coordinate and
     * updates the canvas to reflect any changes.
     *
     * @param x The x coordinate of the clicked pixel.
     * @param y The y coordinate of the clicked pixel.
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

    // ==================== TOOL BAR ====================

    /**
     * @brief Sets the current tool to Standard Brush.
     *
     * Called when the user selects the standard brush tool from the toolbar.
     * Updates currentTool so future canvas input uses the brush behavior.
     */
    void standardBrushSelectedSlot();

    /**
     * @brief Sets the current tool to Eraser.
     *
     * Called when the user selects the eraser tool from the toolbar.
     * Updates currentTool so future canvas input removes color instead of applying it.
     */
    void eraserToolSelectedSlot();

    /**
     * @brief Sets the current tool to Paint Bucket.
     *
     * Called when the user selects the paint bucket tool from the toolbar.
     * Updates currentTool so future canvas input performs a flood fill operation.
     */
    void paintBucketSelectedSlot();

    /**
     * @brief Sets the current tool to Eyedropper.
     *
     * Called when the user selects the eyedropper tool from the toolbar.
     * Updates currentTool so future canvas input samples colors from the sprite.
     */
    void eyeDropperToolSelectedSlot();

    /**
     * @brief Sets the current tool to Mirror.
     *
     * Called when the user selects the mirror tool from the toolbar.
     * Updates currentTool so future canvas input applies mirrored drawing behavior.
     */
    void mirrorToolSelectedSlot();

    /**
     * @brief Sets the current tool to Selection Tool.
     *
     * Called when the user selects the selection tool from the toolbar.
     * Updates currentTool so future canvas input uses selection behavior.
     */
    void selectionToolSelectedSlot();

    /**
     * @brief Updates the current drawing color based on a palette selection.
     *
     * Called when the user clicks on the color palette. Retrieves the color
     * stored at the selected palette position and sets it as currentColor,
     * which will be used for future drawing operations.
     *
     * @param x The x coordinate in the color palette.
     * @param y The y coordinate in the color palette.
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
