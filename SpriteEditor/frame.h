#ifndef FRAME_H
#define FRAME_H

#include <QObject>

class frame : public QObject
{
    Q_OBJECT
public:
    explicit frame(QObject *parent = nullptr);

signals:
};

#endif // FRAME_H
