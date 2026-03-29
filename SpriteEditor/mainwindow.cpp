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
#include <iostream>
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    control = new Controller(this);

    //Connecting signal new project in mainwindow to slot newProjectSlot in controller
    connect(this, &MainWindow::newProject, control, &Controller::newProjectSlot);

    connect(this, &MainWindow::canvasInput, control, &Controller::handleCanvasInputSlot);

    // Direct connection from Toolbar to Controller
    connect(ui->widget, &toolbar::paintBucketSelected, control, &Controller::paintBucketSelectedSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_actionSave_triggered()
{
    std::cout << "hello world" << std::endl;
}



void MainWindow::on_actionNew_triggered()
{

    int spriteSize = QInputDialog::getInt(nullptr, "New Srite Wizard", "Please enter the resolution", QLineEdit::Normal);

    emit newProject(spriteSize);
}


void MainWindow::on_pushButton_clicked()
{
    emit canvasInput(0,0);
}

void MainWindow::on_fillBucket_clicked()
{
    emit fillBucketSelected();
}
