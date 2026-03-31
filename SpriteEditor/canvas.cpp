#include "canvas.h"
#include "qpushbutton.h"
#include "ui_canvas.h"

Canvas::Canvas(int width, int height, int tileSize, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Canvas)
{
    ui->setupUi(this);

    setFixedSize(width, height);

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(0);
    grid->setContentsMargins(0,0,0,0);

    int cols = width / tileSize;
    int rows = height / tileSize;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            auto* btn = new QPushButton(this);
            btn->setFixedSize(tileSize, tileSize);
            grid->addWidget(btn, r, c);
        }
    }

    setLayout(grid);
    setMinimumSize(150, 150);
    render = QImage(spriteWidth, spriteHeight, QImage::Format_ARGB32_Premultiplied);
    render.fill(Qt::transparent);
}

Canvas::~Canvas()
{
    delete ui;
}


