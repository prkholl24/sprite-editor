/**
 * @file canvas.cpp
 * @brief implementation of the Canvas widget
 *
 * Displays the Frame data and processes inputs to send back to the controller
 *
 * Team: Green Goombas
 * github url: https://github.com/UofU-CS3505/cs3505-assignment8-GreenGoombas.git
 * @authors Charles Adair, Armando Carrillo, Parker Hollingsed,
 *          Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3/30/2026
 *
 * Last Revision: 3/30/2026 12:56AM MST by Charles Adair
 */

#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Canvas)
    , spriteWidth(16)
    , spriteHeight(16)
{
    ui->setupUi(this);
    setMinimumSize(150, 150);
    render = QImage(spriteWidth, spriteHeight, QImage::Format_ARGB32_Premultiplied);
    render.fill(Qt::transparent);
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::clear() {
    render.fill(Qt::transparent);
    update();
}

void Canvas::drawPixel(int x, int y, std::vector<int> color) {
    if (x < 0 || x >= spriteWidth || y < 0 || y >= spriteHeight)
        return;
    
    QColor qcolor(color[0], color[1], color[2], color[3]);
    
    QPainter painter(&render);
    // Use SourceOver to blend colors (especially useful for tweening layer)
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setPen(qcolor);
    painter.drawPoint(x, y);
    update();
}

void Canvas::initialize(int width, int height) {
    spriteWidth = width;
    spriteHeight = height;
    render = QImage(spriteWidth, spriteHeight, QImage::Format_ARGB32_Premultiplied);
    render.fill(Qt::transparent);
    update();
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    // Takes the data stored into `render` and blows it up to fill 500x500 pixels.
    QImage scaled = render.scaled(size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    int x = (width() - scaled.width()) / 2;
    int y = (height() - scaled.height()) / 2;

    painter.drawImage(x, y, scaled);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPoint spritePos = mapToSprite(event->pos());
        if (spritePos.x() != -1) {
            emit canvasInputSignal(spritePos.x(), spritePos.y());
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint spritePos = mapToSprite(event->pos());
        if (spritePos.x() != -1) {
            emit canvasInputSignal(spritePos.x(), spritePos.y());
        }
    }
}

QPoint Canvas::mapToSprite(const QPoint &pos) const {

    // Scales the input down to the spriteHeight and spriteWidth and determines which
    // pixel is equivalent.
    QImage scaled = render.scaled(size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    int offsetX = (width() - scaled.width()) / 2;
    int offsetY = (height() - scaled.height()) / 2;

    int relativeX = pos.x() - offsetX;
    int relativeY = pos.y() - offsetY;

    int spriteX = (relativeX * spriteWidth) / scaled.width();
    int spriteY = (relativeY * spriteHeight) / scaled.height();

    spriteX = std::max(0, std::min(spriteX, spriteWidth - 1));
    spriteY = std::max(0, std::min(spriteY, spriteHeight - 1));

    return QPoint(spriteX, spriteY);
}
