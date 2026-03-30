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


Controller::Controller(QWidget *parent)
{
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
    }
    else {
        QMessageBox::warning(nullptr, "Error", "Please load or create a new model in the File tab first.");
    }
}

/// TOOL METHODS ///
void Controller::standardBrush(int x, int y){
    ///TODO: Manipulate the sprite to draw one pixel using standardBrush.
}

void Controller::eraserTool(int x, int y){
    ///TODO: ERASE ONE PIXEL IN SPRITE
}

void Controller::fillBucket(int x, int y){
    ///TODO: FILL AREA WITHIN ENCLOSED SPACE.
    std::vector<int> oldColor = currentFrame->pixels[x][y].getColor();
    if (oldColor == currentColor)
        return;
    fillBucketLogic(currentFrame->pixels,x, y, oldColor);
}

void Controller::eyeDropperTool(int x, int y){
    ///TODO: SAVES A SELECTED COLOR AT GIVEN PIXEL
}

void Controller::mirrorTool(int x, int y){
    ///TODO: MIRROR TOOL
}

void Controller::selectionTool(int x, int y){
    ///TODO: SELECTION TOOL
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



//TOOLBAR
//Signal is received from toolbar.
//That updates the status (enum) in controller or wherever for the left click behavior
//This alters what happens when the left button on the mouse is clicked.
