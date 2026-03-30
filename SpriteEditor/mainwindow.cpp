/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class
 *
 * UI component initialized on execution upon which each of the disparate UI components sits.
 * Also initializes the Controller and interfaces with its slots and signals.
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/29/2026
 *
 * Last Revision: 3/29/2026 12:54AM MST by Charles Adair
 */

// TO-DO move all includes to .h file
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    control = new Controller(this);

    //Connecting signal new project in mainwindow to slot newProjectSlot in controller
    connect(this, &MainWindow::newProjectSignal, control, &Controller::newProjectSlot);

    connect(this, &MainWindow::loadProjectSignal, control, &Controller::loadProjectSlot);

    connect(this, &MainWindow::saveProjectSignal, control, &Controller::saveProjectSlot);

    connect(this, &MainWindow::canvasInput, control, &Controller::handleCanvasInputSlot);

    // Direct connection from Toolbar to Controller
    connect(ui->toolbarWidget, &toolbar::standardBrushSelectedSignal, control, &Controller::standardBrushSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::eraserToolSelectedSignal, control, &Controller::eraserToolSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::paintBucketSelectedSignal, control, &Controller::paintBucketSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::eyeDropperToolSelectedSignal, control, &Controller::eyeDropperToolSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::mirrorToolSelectedSignal, control, &Controller::mirrorToolSelectedSlot);

    connect(ui->toolbarWidget, &toolbar::selectionToolSelectedSignal, control, &Controller::selectionToolSelectedSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    emit saveProjectSignal();
}


/// TEST SLOTS MEANT FOR TESTING ///
void MainWindow::on_actionNew_triggered()
{

    int spriteSize = QInputDialog::getInt(nullptr, "New Srite Wizard", "Please enter the resolution", QLineEdit::Normal);

    emit newProjectSignal(spriteSize);
}

void MainWindow::on_pushButton_clicked()
{
    emit canvasInput(0,0);
}

void MainWindow::on_actionLoad_triggered()
{
    emit loadProjectSignal();
}

