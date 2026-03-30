#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Canvas)
    , spriteWidth(16)
    , spriteHeight(16)
{
    ui->setupUi(this);
    render = QImage(spriteWidth, spriteHeight, QImage::Format_ARGB32_Premultiplied);
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::drawPixel(int x, int y, std::vector<int> color) {
    return;
}

void Canvas::initialize(int width, int height) {
    spriteWidth = width;
    spriteHeight = height;
    render = QImage(spriteWidth, spriteHeight, QImage::Format_ARGB32_Premultiplied);
    render.fill(Qt::transparent);
    update();
}

void Canvas::paintEvent(QPaintEvent *event) {
    return;
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    return;
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    return;
}

QPoint Canvas::mapToSprite(const QPoint &pos) const {
    return pos;
}
