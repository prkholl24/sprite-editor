#ifndef SPRITE_H
#define SPRITE_H

#include "frame.h"
#include <QObject>

class Sprite : public QObject
{
    Q_OBJECT
private:
    std::vector<Frame> frames;

    int fps;

    int currentFrame;

public:
    explicit Sprite(QObject *parent = nullptr);

    void addFrame(Frame frame);
        frames.push_back(frame);

    Frame getCurrentFrame();

    void setFPS(int fps);

    int getFrameCount();

    void swapFrame();

    void duplicateFrame();



signals:
};

#endif // SPRITE_H
