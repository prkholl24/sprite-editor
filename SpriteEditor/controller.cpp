#include "controller.h"
#include "QAction"
#include <QInputDialog>
#include <iostream>

Controller::Controller(QWidget *parent)
{
    currentTool = ToolStates::StandardBrush;

}

void savePressed();


void Controller::newProjectSlot(int spriteSize){


}


void Controller::handleCanvasInputSlot(int x, int y){

    switch(currentTool)




}


void Controller::fillBucket(int x, int y){


}


//TOOLBAR
//Signal is received from toolbar.
//That updates the status (enum) in controller or wherever for the left click behavior
//This alters what happens when the left button on the mouse is clicked.
