#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "frame.h"
#include "qpixmap.h"
#include <QObject>
#include <vector>

class controller : public QObject
{
    Q_OBJECT
public:
    explicit controller(QObject *parent = nullptr);

private:


signals:
    // sends the pixmap over to the view.
    void sendPixmap(int index, QPixmap map);

public slots:
    /**
     * @brief Receives a frame from the Model, and converts it to a pix map.
     * Does this via "emit sendPixmap(pixmap-you-just-made)".
     * @param index The index of the frame button to update
     * @param frame The frame to convert
     */
    void convertToPixmap(int index, Frame frame);

    /**
     * @brief Converts all frames to pixmaps and sends them to the timeline.
     * Use this when loading a new sprite or initializing the timeline.
     * @param frames Vector of all frames to convert
     */
    void convertAllFrames(const std::vector<Frame>& frames);

};

#endif // CONTROLLER_H
