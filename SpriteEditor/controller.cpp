#include "controller.h"

controller::controller(QObject *parent)
    : QObject{parent}
{}

void controller::convertToPixmap(Frame frame) {
    QImage image;

    // Get the color from Frame[x][y] and set the corresponding pixel in QImage to that color.
    for (int x = 0; x < frame.getWidth(); x++) {
        for (int y = 0; y < frame.getHeight(); y++) {
            std::vector<int> color = frame.getPixel(x, y).getColor();
            QColor qcolor(color[0], color[1], color[2], color[3]);
            image.setPixelColor(x, y, qcolor);
        }
    }
    int buttonSize = 70; // set the transformed image to be the same size as the buttons
    QPixmap pixmap = QPixmap::fromImage(image.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio, Qt::FastTransformation));
    emit sendPixmap(pixmap);
}
