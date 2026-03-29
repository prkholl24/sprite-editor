#include "toolbar.h"
#include "ui_toolbar.h"

toolbar::toolbar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::toolbar)
{
    ui->setupUi(this);

    //connect

}

toolbar::~toolbar()
{
    delete ui;
}


void toolbar::on_PaintBrush_clicked()
{

}


void toolbar::on_Eraser_clicked()
{

}


void toolbar::on_FillBucket_clicked()
{

}


void toolbar::on_EyeDropper_clicked()
{

}


void toolbar::on_Mirror_clicked()
{

}


void toolbar::on_Selection_clicked()
{

}

