
/**
 * @file canvas.cpp
 * @brief implementation of the Canvas widget
 * Displays the Frame data and processes inputs to send back to the controller
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/29/2026
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
    setMinimumSize(500, 500);
    render = QImage(spriteWidth, spriteHeight, QImage::Format_ARGB32_Premultiplied);
    render.fill(Qt::transparent);
}

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


Canvas::~Canvas()
{
    delete ui;
}


void Canvas::drawPixel(int x, int y, std::vector<int> color) {
    if (x < 0 || x >= spriteWidth || y < 0 || y >= spriteHeight)
        return;
    
    QColor qcolor(color[0], color[1], color[2], color[3]);
    render.setPixelColor(x, y, qcolor);
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
