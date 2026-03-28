#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    Canvas(int w, int h, int tileSize, QWidget* parent);
    ~Canvas();

private:
    Ui::Canvas *ui;
    int width;
    int height;
};

#endif // CANVAS_H
