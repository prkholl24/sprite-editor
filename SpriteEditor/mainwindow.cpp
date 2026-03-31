/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class
 *
 * UI component initialized on execution upon which each of the disparate UI components sits.
 * Also initializes the Controller and interfaces with its slots and signals.
 *
 * Team: Green Goombas
 * github url: https://github.com/UofU-CS3505/cs3505-assignment8-GreenGoombas.git
 * @authors Charles Adair, Armando Carrillo, Parker Hollingsed,
 *          Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3/29/2026
 *
 * Last Revision: 3/29/2026 12:54AM MST by Charles Adair
 */

// TO-DO move all includes to .h file
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "timeline.h"
#include <QAction>
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    control = new Controller();

    //Connecting signal new project in mainwindow to slot newProjectSlot in controller
    connect(this, &MainWindow::newProjectSignal, control, &Controller::newProjectSlot);

    connect(this, &MainWindow::loadProjectSignal, control, &Controller::loadProjectSlot);

    connect(this, &MainWindow::saveProjectSignal, control, &Controller::saveProjectSlot);
  

    // Connects the Canvas to the controller
    connect(ui->canvas, &Canvas::canvasInputSignal, control, &Controller::handleCanvasInputSlot);

    connect(control, &Controller::drawPixel, ui->canvas, &Canvas::drawPixel);

    connect(control, &Controller::clearCanvas, ui->canvas, &Canvas::clear);

    connect(control, &Controller::initializeCanvas, ui->canvas, &Canvas::initialize);
    connect(control, &Controller::initializeCanvas, ui->preview, &Canvas::initialize);

    // Connects the Color Pallete to the controller
    connect(ui->colorPalette, &Canvas::canvasInputSignal, control, &Controller::handleColorPaletteInput);

    connect(control, &Controller::drawColorPalettePixel, ui->colorPalette, &Canvas::drawPixel);

    connect(control, &Controller::initializeColorPalette, ui->colorPalette, &Canvas::initialize);

    // Color tab in the main window connects to the Controller slots for updating the color palette
    connect(ui->actionColorWheel, &QAction::triggered, control, &Controller::defaultPaletteSelected);

    connect(ui->actionArt_Deco, &QAction::triggered, control, &Controller::artDecoPaletteSelected);

    connect(ui->actionRetro_Pastel, &QAction::triggered, control, &Controller::retroPastelPaletteSelected);

    connect(ui->action60s_Pop, &QAction::triggered, control, &Controller::sixtiesPopPaletteSelected);

    connect(ui->action70s_Earth, &QAction::triggered, control, &Controller::seventiesEarthPaletteSelected);

    connect(ui->action80s_Neon, &QAction::triggered, control, &Controller::eightiesNeonPaletteSelected);

    // Direct connection from Toolbar to Controller
    connect(ui->toolbarWidget, &toolbar::standardBrushSelectedSignal, control, &Controller::standardBrushSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::eraserToolSelectedSignal, control, &Controller::eraserToolSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::paintBucketSelectedSignal, control, &Controller::paintBucketSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::eyeDropperToolSelectedSignal, control, &Controller::eyeDropperToolSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::mirrorToolSelectedSignal, control, &Controller::mirrorToolSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::selectionToolSelectedSignal, control, &Controller::selectionToolSelectedSlot);

    // Initialize the color palette when the application starts
    control->initializePalette();
    
    // Preview widget connection
    connect(control, &Controller::drawPreviewPixel, ui->preview, &Canvas::drawPixel);
    
    // Timeline connections
    connect(ui->timelineWidget, &Timeline::frameSelected, control, &Controller::frameSelectedSlot);
    connect(ui->timelineWidget, &Timeline::frameAdded, control, &Controller::addFrameSlot);
    connect(ui->timelineWidget, &Timeline::frameRemoved, control, &Controller::removeFrameSlot);
    connect(ui->timelineWidget, &Timeline::fpsChanged, control, &Controller::setSpriteFPS);

    // Controller -> Timeline sync
    connect(control, &Controller::setTimelineFrameCount, ui->timelineWidget, &Timeline::setFrameCount);
    connect(control, &Controller::sendPixmap, ui->timelineWidget, &Timeline::updateButtonImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Sprite", "", "JSON Files (*.json);;All Files (*)");

    if(fileName.isEmpty()){
        return;
    }

    emit saveProjectSignal(fileName);
}


void MainWindow::on_actionLoad_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Load Sprite", "", "SSP Files (*.ssp);;JSON Files (*.json);;All Files (*)");

    if(fileName.isEmpty()){
        return;
    }

    emit loadProjectSignal(fileName);
}

/// TEST SLOTS MEANT FOR TESTING ///
void MainWindow::on_actionNew_triggered()
{

    int spriteSize = QInputDialog::getInt(nullptr, "New Srite Wizard", "Please enter the resolution", QLineEdit::Normal);

    emit newProjectSignal(spriteSize);
}

