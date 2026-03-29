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
            fillBucket();
            std::cout << "Fill bucket selected!" << std::endl;
            break;
        case ToolStates::StandardBrush:
            std::cout << "Standard brush selected!" << std::endl;
            break;
        case ToolStates::Eraser:
        case ToolStates::Eyedropper:
        case ToolStates::Mirror:
        case ToolStates::SelectionTool:
            break;
        }
    }
    else {
        QMessageBox::warning(nullptr, "Error", "Please load or create a new model in the File tab first.");
    }
}


void Controller::fillBucket(){
    // Parameters x and y go unused, but are required in the signature in
    // order to called by using the same method signature as other tools.
    for (int i = 0; i < model->getWidth(); i++) {
        for (int j = 0; j < model->getHeight(); j++) {
            currentFrame->getPixel(i, j).setColor(currentColor);
        }
    }

}

void Controller::paintBucketSelectedSlot() {
    currentTool = ToolStates::PaintBucket;
}


//TOOLBAR
//Signal is received from toolbar.
//That updates the status (enum) in controller or wherever for the left click behavior
//This alters what happens when the left button on the mouse is clicked.
