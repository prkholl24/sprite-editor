/**
 * @file controller.cpp
 * @brief implementation of the Controller class
 *
 * This class handles the relationship between the Sprite model and the Graphical User Interface
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/29/2026
 *
 * Last Revision: 3/29/2026 12:51AM MST by Charles Adair
 */
// TO-DO move all includes to .h file
#include "controller.h"
#include <QMessageBox>
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileDialog>



Controller::Controller(QWidget *parent)
{
    // Starts a new thread to continuously cycle through frames for the preview
    initializePreviewTimer();
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

void Controller::setSpriteFPS(int fps) {
    model->setFPS(fps);
    if (fps > 0) {
        previewTimer->start(1000 / fps);
    } else {
        previewTimer->stop();
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

    currentFrameIndex = 0;
    currentFrame = &model->getFrame(0);
    currentColor = {255, 0, 0, 255}; // Default to red for new projects

    emit initializeCanvas(spriteSize, spriteSize);
    emit setTimelineFrameCount(model->getFrameCount());
    updateCanvas();

    // Start the preview timer
    previewFrameIndex = 0;
    previewTimer->start(1000 / model->getFPS());
    convertToPixmap(0, *currentFrame);

}

void Controller::loadProjectSlot(QString filePath){
    QFile file(filePath);

    std::cout << "in load project slot" << std::endl;

    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    std::cout << "Line 85 above Sprite::fromJson" << std::endl;
    model = Sprite::fromJson(doc.object());



    int spriteSize = model->getHeight();

    emit initializeCanvas(spriteSize, spriteSize);
    emit setTimelineFrameCount(model->getFrameCount());
    updateCanvas();

    // Start the preview timer
    previewFrameIndex = 0;
    previewTimer->start(1000 / model->getFPS());
    convertToPixmap(0, *currentFrame);



}

void Controller::saveProjectSlot(QString filePath){
    QJsonObject object = model->toJson();

    QJsonDocument output(object);

    QByteArray data = output.toJson();

    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly)){
        return;
    }

    file.write(data);
    file.close();


}


void Controller::updateCanvas() {
    if (!currentFrame)
        return;

    emit clearCanvas();

    // Draw the previous frame with reduced opacity (Tweening/Onion Skinning)
    if (model->getFrameCount() > 0 && currentFrameIndex > 0) {
        Frame& tweeningLayer = model->getFrame(currentFrameIndex - 1);
        for (int x = 0; x < currentFrame->getWidth(); ++x) {
            for (int y = 0; y < currentFrame->getHeight(); ++y) {
                std::vector<int> color = tweeningLayer.getPixel(x, y).getColor();
                // Only draw if the previous frame pixel wasn't transparent
                if (color[3] > 0) {
                    color[3] = (255 / 4); // Make it quite transparent
                    emit drawPixel(x, y, color);
                }
            }
        }
    }

    // Draw the current frame
    for (int x = 0; x < currentFrame->getWidth(); ++x) {
        for (int y = 0; y < currentFrame->getHeight(); ++y) {
            std::vector<int> color = currentFrame->getPixel(x, y).getColor();
            // Draw all pixels from current frame. 
            // If it's transparent (alpha 0), it won't overwrite the tweening layer 
            // because Canvas::drawPixel now uses SourceOver blending.
            emit drawPixel(x, y, color);
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

        // Update the current frame's thumbnail in the timeline
        convertToPixmap(currentFrameIndex, *currentFrame);
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
        colorPalette = artDecoPalette();
        break;
    case PaletteType::RetroPastel:
        colorPalette = retroPastelPalette();
        break;
    case PaletteType::SixtiesPop:
        colorPalette = sixtiesPopPalette();
        break;
    case PaletteType::SeventiesEarth:
        colorPalette = seventiesEarthPalette();
        break;
    case PaletteType::EightiesNeon:
        colorPalette = eightiesNeonPalette();
        break;
    }
    updateColorPalette();
}

void Controller::defaultPaletteSelected() {
    selectedPalette = PaletteType::Default;
    initializePalette();
}

void Controller::artDecoPaletteSelected() {
    selectedPalette = PaletteType::ArtDecoGold;
    initializePalette();
}

void Controller::retroPastelPaletteSelected() {
    selectedPalette = PaletteType::RetroPastel;
    initializePalette();
}

void Controller::sixtiesPopPaletteSelected() {
    selectedPalette = PaletteType::SixtiesPop;
    initializePalette();
}

void Controller::seventiesEarthPaletteSelected() {
    selectedPalette = PaletteType::SeventiesEarth;
    initializePalette();
}

void Controller::eightiesNeonPaletteSelected() {
    selectedPalette = PaletteType::EightiesNeon;
    initializePalette();
}

Frame* Controller::eightiesNeonPalette(){
    Frame* palette = new Frame(3,3);

    palette->getPixel(0,0).setColor(std::vector<int> {0, 133, 202, 255});  // Process Blue
    palette->getPixel(1,0).setColor(std::vector<int> {120, 190, 32, 255}); // Pantone 7488 Green
    palette->getPixel(2,0).setColor(std::vector<int> {255, 215, 0, 255});  // Yellow 012

    palette->getPixel(0,1).setColor(std::vector<int> {232, 170, 66,255});  // Pantone 1575
    palette->getPixel(1,1).setColor(std::vector<int> {255, 102, 0, 255});  // Orange 021
    palette->getPixel(2,1).setColor(std::vector<int> {123, 64, 129, 255}); // Pantone 213 Pink

    palette->getPixel(0,2).setColor(std::vector<int> {237, 41, 57, 255});  // Rhodamine Red
    palette->getPixel(1,2).setColor(std::vector<int> {16, 24, 32, 255});   // Black 6
    palette->getPixel(2,2).setColor(std::vector<int> {255, 255, 255, 255});// White (neutral)

    return palette;
}

Frame* Controller::seventiesEarthPalette() {
    Frame* palette = new Frame(3,2);

    palette->getPixel(0,0).setColor(std::vector<int> {107, 122, 58, 255});  // Avocado
    palette->getPixel(1,0).setColor(std::vector<int> {168, 160, 60, 255});  // Golden Olive
    palette->getPixel(2,0).setColor(std::vector<int> {238, 220, 130, 255}); // Cream Gold

    palette->getPixel(0,1).setColor(std::vector<int> {201, 152, 36, 255});  // Harvest Gold
    palette->getPixel(1,1).setColor(std::vector<int> {204, 85, 0, 255});    // Burnt Orange
    palette->getPixel(2,1).setColor(std::vector<int> {112, 66, 20, 255});   // Tortoise Shell

    return palette;
}

Frame* Controller::sixtiesPopPalette() {
    Frame* palette = new Frame(3, 3);

    palette->getPixel(0,0).setColor({166, 25, 46, 255});   // 7621 Red
    palette->getPixel(1,0).setColor({255, 111, 0, 255});   // 158 Orange
    palette->getPixel(2,0).setColor({0, 121, 140, 255});   // 7713 Teal

    palette->getPixel(0,1).setColor({0, 132, 61, 255});    // 340 Green
    palette->getPixel(1,1).setColor({167, 219, 216, 255}); // 318 Light Aqua
    palette->getPixel(2,1).setColor({240, 163, 188, 255}); // 516 Pink

    palette->getPixel(0,2).setColor({109, 57, 139, 255});  // 7662 Purple
    palette->getPixel(1,2).setColor({181, 206, 8, 255});   // 7744 Lime
    palette->getPixel(2,2).setColor({255, 184, 28, 255});  // 1235 Yellow

    return palette;
}

Frame* Controller::retroPastelPalette() {
    Frame* palette = new Frame(3,2);

    palette->getPixel(0,0).setColor({244, 221, 224, 255}); // 9286 Blush Pink
    palette->getPixel(1,0).setColor({178, 214, 204, 255}); // 5483 Mint
    palette->getPixel(2,0).setColor({245, 236, 180, 255}); // 9140 Pale Yellow

    palette->getPixel(0,1).setColor({185, 205, 230, 255}); // 9402 Baby Blue
    palette->getPixel(1,1).setColor({240, 205, 170, 255}); // 9200 Peach
    palette->getPixel(2,1).setColor({225, 210, 230, 255}); // 9340 Lavender

    return palette;
}

Frame* Controller::artDecoPalette() {
    Frame* palette = new Frame(3, 2);

    palette->getPixel(0,0).setColor({140, 130, 180, 255}); // Lavender Violet
    palette->getPixel(1,0).setColor({235, 230, 220, 255}); // Turtledove
    palette->getPixel(2,0).setColor({210, 190, 150, 255}); // Champagne Beige

    palette->getPixel(0,1).setColor({196, 98, 40, 255});   // Carnelian
    palette->getPixel(1,1).setColor({20, 20, 20, 255});    // Jet Black
    palette->getPixel(2,1).setColor({180, 180, 185, 255}); // Silver

    return palette;
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

void Controller::handleAddFrame() {
    model->addFrame();
}

void Controller::handleRemoveFrame(int index) {
    model->removeFrame(index);
}

void Controller::handleFrameSelected(int index) {
    currentFrame = &model->getFrame(index);
    updateCanvas();
}

void Controller::initializePreviewTimer() {
    if (!previewTimer) {
        previewTimer = new QTimer(this);
        connect(previewTimer, &QTimer::timeout, this, &Controller::updatePreview);
    }
}

void Controller::updatePreview() {
    if (!model)
        return;

    // Chooses the next frame or loops back to the first frame.
    previewFrameIndex = (previewFrameIndex + 1) % model->getFrameCount();
    Frame& frame = model->getFrame(previewFrameIndex);

    // Draws to the preview.
    for (int x = 0; x < frame.getWidth(); ++x) {
        for (int y = 0; y < frame.getHeight(); ++y) {
            emit drawPreviewPixel(x, y, frame.getPixel(x, y).getColor());
        }
    }
}

/// TIMELINE SLOTS ///
void Controller::frameSelectedSlot(int index) {
    if (!model)
        return;

    if (index < 0 || index >= model->getFrameCount())
        return;

    currentFrameIndex = index;
    currentFrame = &model->getFrame(index);
    updateCanvas();
}

void Controller::addFrameSlot(int index) {
    if (!model)
        return;

    model->addFrame();
    // Update the new frame's thumbnail
    convertToPixmap(model->getFrameCount() - 1, model->getFrame(model->getFrameCount() - 1));
}

void Controller::removeFrameSlot(int index) {
    if (!model)
        return;

    model->removeFrame(index);

    // Adjust current frame index if needed
    if (currentFrameIndex >= model->getFrameCount()) {
        currentFrameIndex = model->getFrameCount() - 1;
    }
    currentFrame = &model->getFrame(currentFrameIndex);
    updateCanvas();
}

//TOOLBAR
//Signal is received from toolbar.
//That updates the status (enum) in controller or wherever for the left click behavior
//This alters what happens when the left button on the mouse is clicked.
