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

