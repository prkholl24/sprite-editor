/**
 * @file controller.cpp
 * @brief implementation of the Controller class
 *
 * This class handles the relationship between the Sprite model and the Graphical User Interface
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/29/2026
 *
 * Last Revision: 3/30/2026 2:39PM MST by Charles Adair
 */
// TO-DO move all includes to .h file
#include "controller.h"
#include <QMessageBox>
#include <iostream>

Controller::Controller(QWidget *parent)
{
}

void Controller::convertToPixmap(int index, Frame frame) {
    QImage image(frame.getWidth(), frame.getHeight(), QImage::Format_RGBA8888);

    // Get the color from Frame[x][y] and set the corresponding pixel in QImage to that color.
    for (int x = 0; x < frame.getWidth(); x++) {
        for (int y = 0; y < frame.getHeight(); y++) {
            std::vector<int> color = frame.getPixel(x, y).getColor();
            QColor qcolor(color[0], color[1], color[2], color[3]);
            image.setPixelColor(x, y, qcolor);
        }
    }
    int buttonSize = 70; // set the transformed image to be the same size as the buttons
    QPixmap pixmap = QPixmap::fromImage(image.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio, Qt::FastTransformation));
    emit sendPixmap(index, pixmap);
}

void Controller::convertAllFrames(const std::vector<Frame>& frames) {
    for (size_t i = 0; i < frames.size(); ++i) {
        convertToPixmap(static_cast<int>(i), frames[i]);
    }
}

void Controller::fillBucketLogic(std::vector<std::vector<Pixel>>& pixelGrid, int x, int y, std::vector<int> oldColor) {
    int gridSize = pixelGrid.size();

    ///Base Case for recursive fillBucketLogic
    if (x < 0 || x >= gridSize || y < 0 || y >= gridSize || pixelGrid[x][y].getColor() != oldColor)
        return;
    pixelGrid[x][y].setColor(currentColor);

    fillBucketLogic(pixelGrid,x+1,y,oldColor);
    fillBucketLogic(pixelGrid,x-1,y,oldColor);
    fillBucketLogic(pixelGrid,x,y+1,oldColor);
    fillBucketLogic(pixelGrid,x,y-1,oldColor);
}

void savePressed();


void Controller::newProjectSlot(int spriteSize){
    if (model) {
        delete model;
    }
    model = new Sprite(spriteSize, spriteSize);
    currentFrame = &model->getFrame(0);
    currentColor = {255, 0, 0, 255}; // Default to red for new projects

    emit initializeCanvas(spriteSize, spriteSize);
    updateCanvas();
}


void Controller::updateCanvas() {
    if (!currentFrame)
        return;

    for (int x = 0; x < currentFrame->getWidth(); ++x) {
        for (int y = 0; y < currentFrame->getHeight(); ++y) {
            emit drawPixel(x, y, currentFrame->getPixel(x, y).getColor());
        }
    }
}


void Controller::handleCanvasInputSlot(int x, int y){
    if (!(model == nullptr)) {
        switch(currentTool) {

        case ToolStates::PaintBucket:
            fillBucket(x,y);
            std::cout << "Fill bucket selected!" << std::endl;
            break;
        case ToolStates::StandardBrush:
            standardBrush(x,y);
            std::cout << "Standard brush selected!" << std::endl;
            break;
        case ToolStates::Eraser:
            eraserTool(x,y);
            std::cout << "Eraser tool selected!" << std::endl;
            break;
        case ToolStates::Eyedropper:
            eyeDropperTool(x,y);
            std::cout << "Eye dropper tool selected!" << std::endl;
            break;
        case ToolStates::Mirror:
            mirrorTool(x,y);
            std::cout << "Mirror tool selected!" << std::endl;
            break;
        case ToolStates::SelectionTool:
            selectionTool(x,y);
            std::cout << "Selection tool selected!" << std::endl;
            break;
        }

        // Refresh the canvas to reflect changes
        updateCanvas();
    }
    else {
        QMessageBox::warning(nullptr, "Error", "Please load or create a new model in the `File` tab first.");
    }
}

/// TOOL METHODS ///
void Controller::standardBrush(int x, int y){
    currentFrame->getPixel(x,y).setColor(currentColor);
}

void Controller::eraserTool(int x, int y){
    std::vector<int> defaultBackgroundColor = {0,0,0,0};
    currentFrame->getPixel(x,y).setColor(defaultBackgroundColor);
}

void Controller::fillBucket(int x, int y){
    std::vector<int> oldColor = currentFrame->pixels[x][y].getColor();
    if (oldColor == currentColor)
        return;
    fillBucketLogic(currentFrame->pixels,x, y, oldColor);
}

void Controller::eyeDropperTool(int x, int y){
    currentColor = currentFrame->getPixel(x,y).getColor();
}

void Controller::mirrorTool(int x, int y){

    int halfCanvas = currentFrame->pixels.size() / 2;
    int offset;

    standardBrush(x,y);

    /// LEFT
    if (x < halfCanvas){
        offset = halfCanvas - x;
        standardBrush(halfCanvas+offset,y);
    /// RIGHT
    } else {
        offset = x - halfCanvas;
        standardBrush(halfCanvas-offset,y);
    }
}

void Controller::selectionTool(int x, int y){
    ///TODO: SELECTION TOOL
    ///
    /// OVERDIE MOSUECLICK (X,Y) TOGGLE
    ///
    /// OVERRIDE MOUSEDRAGED (X,Y) TOGGLE
}


/// CURRENT TOOL SLOTS ///
void Controller::standardBrushSelectedSlot(){
    currentTool = ToolStates::StandardBrush;
    std::cout << "1 selected!" << std::endl;
}
void Controller::eraserToolSelectedSlot(){
    currentTool = ToolStates::Eraser;
    std::cout << "2 selected!" << std::endl;
}
void Controller::paintBucketSelectedSlot(){
    currentTool = ToolStates::PaintBucket;
    std::cout << "3 selected!" << std::endl;
}
void Controller::eyeDropperToolSelectedSlot(){
    currentTool = ToolStates::Eyedropper;
    std::cout << "4 selected!" << std::endl;
}
void Controller::mirrorToolSelectedSlot(){
    currentTool = ToolStates::Mirror;
    std::cout << "5 selected!" << std::endl;
}
void Controller::selectionToolSelectedSlot(){
    currentTool = ToolStates::SelectionTool;
    std::cout << "6 selected!" << std::endl;
}

void Controller::updateColorPalette() {
    if (!colorPalette)
        return;

    emit initializeColorPalette(colorPalette->getWidth(), colorPalette->getHeight());

    for (int x = 0; x < colorPalette->getWidth(); x++) {
        for (int y = 0; y < colorPalette->getHeight(); y++) {
            emit drawColorPalettePixel(x, y, colorPalette->getPixel(x, y).getColor());
        }
    }
}

void Controller::handleColorPaletteInput(int x, int y) {
    if (colorPalette != nullptr) {
        currentColor = colorPalette->getPixel(x, y).getColor();
    }
}

void Controller::initializePalette() {
    if (colorPalette) {
        delete colorPalette;
    }

    switch (selectedPalette) {
    case PaletteType::Default:
        colorPalette = defaultPalette();
        break;
    case PaletteType::ArtDecoGold:
    case PaletteType::RetroPastel:
    case PaletteType::SixtiesPop:
    case PaletteType::SeventiesEarth:
    case PaletteType::EightiesNeon:
        break;
    }
    updateColorPalette();
}

Frame* Controller::eightiesNeonPalette(){
    Frame* eightiesPalette = new Frame(3,3);

    eightiesPalette->getPixel(0,0).setColor(std::vector<int> {0,0,0,255});
    eightiesPalette->getPixel(1,1).setColor(std::vector<int> {123,0,0,255});
    return eightiesPalette;
}

Frame* Controller::seventiesEarthPalette() {
    return new Frame();
}

Frame* Controller::sixtiesPopPalette() {
    return new Frame();
}

Frame* Controller::retroPastelPalette() {
    return new Frame();
}

Frame* Controller::artDecoPalette() {
    return new Frame();
}

Frame* Controller::defaultPalette() {
    int size = 50;
    Frame* palette = new Frame(size, size);

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {

            // Determines the relative location of the current x and y to the size of the palette.
            double xRatio = static_cast<double>(x) / (size - 1);
            double yRatio = static_cast<double>(y) / (size - 1);

            // As xRatio increases, Red goes down to 0, and Green goes up to 255
            double topR = 255.0 * (1.0 - xRatio);
            double topG = 255.0 * xRatio;
            double topB = 0.0;

            // As xRatio increases, Blue stays 255, Red and Green go up to 255
            double botR = 255.0 * xRatio;
            double botG = 255.0 * xRatio;
            double botB = 255.0;

            // Linear interpolation (LERP) mixes the colors bases on how close this
            // pixel is to the bottom vs top.
            int r = static_cast<int>(topR * (1.0 - yRatio) + botR * yRatio);
            int g = static_cast<int>(topG * (1.0 - yRatio) + botG * yRatio);
            int b = static_cast<int>(topB * (1.0 - yRatio) + botB * yRatio);

            if (r > 255) { r = 255; }
            if (g > 255) { g = 255; }
            if (b > 255) { b = 255; }

            palette->getPixel(x, y).setColor({r, g, b, 255});
        }
    }
    return palette;
}

//TOOLBAR
//Signal is received from toolbar.
//That updates the status (enum) in controller or wherever for the left click behavior
//This alters what happens when the left button on the mouse is clicked.
