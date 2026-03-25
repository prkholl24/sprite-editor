#ifndef FRAME_H

#define FRAME_H

#include <QObject>
#include "pixel.h"

class Frame : public QObject
{
    Q_OBJECT
public:
    explicit Frame(QObject *parent = nullptr);

    Pixel& getPixel(int x, int y);

    void setPixel(int x, int y, Pixel& p);

    void setResolution(int w, int h);

    void clearAll();
private:
    std::vector<std::vector<Pixel>> pixels;

    int width;

    int height;

signals:
};

#endif // FRAME_H
