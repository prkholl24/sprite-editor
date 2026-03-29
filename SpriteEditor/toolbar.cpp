
/**
 * @file toolbar.cpp
 * @brief Implementation of the Toolbar UI
 *
 * // TO-DO: Fill this in
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/29/2026
 *
 * Last Revision: 3/29/2026 10:54AM MST by Armando Carrillo
 */
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
    emit paintBucketSelected();
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

