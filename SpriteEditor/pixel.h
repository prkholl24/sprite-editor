#ifndef PIXEL_H
#define PIXEL_H

#include <QObject>

class pixel : public QObject
{
    Q_OBJECT
public:
    explicit pixel(QObject *parent = nullptr);

signals:
};

#endif // PIXEL_H
