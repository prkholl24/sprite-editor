#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>

class sprite : public QObject
{
    Q_OBJECT
public:
    explicit sprite(QObject *parent = nullptr);

signals:
};

#endif // SPRITE_H
