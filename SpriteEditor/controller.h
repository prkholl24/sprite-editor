#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "frame.h"
#include "qpixmap.h"
#include <QObject>

class controller : public QObject
{
    Q_OBJECT
public:
    explicit controller(QObject *parent = nullptr);

private:


signals:
    // sends the pixmap over to the view.
    void sendPixmap(QPixmap map);

private slots:
    /**
     * @brief Receives a frame from the Model, and converts it to a pix map.
     * Does this via "emit sendPixmap(pixmap-you-just-made)".
     * @param frame
     * @return
     */
    void convertToPixmap(Frame frame);

};

#endif // CONTROLLER_H
