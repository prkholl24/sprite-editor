#ifndef TIMELINE_H
#define TIMELINE_H

#include "controller.h"
#include <QWidget>
#include <QPushButton>
#include <QList>

namespace Ui {
class Timeline;
}


class Timeline : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Default Constructor for Timeline.
     * @param parent: the window to which the Timeline belongs to.
     */
    explicit Timeline(QWidget *parent = nullptr, Controller* controller = nullptr);

    /**
     * @brief The default destructor for Timeline.
     */
    ~Timeline();

    /**
     * @brief Adds a new frame to the end of the timeline.
     */
    void addFrame();

    /**
     * @brief removes the frame from the desired index then shrinks the array.
     * @param The index to remove the frame
     */
    void removeFrame(int index);

    /**
     * @brief Returns the number of frames in the Frames array
     * @return The number of frames in the frames array.
     */
    int frameCount() const;

    /**
     * @brief Returns the index of the frame that is currently selected in the timeline.
     * @return The index of the frame that is selected.
     */
    int selectedFrame() const;

    /**
     * @brief Updates the SelectedFrame variable to the currently selected frame.
     * @param The index of the frame that should be selected.
     */
    void selectFrame(int index);

    /**
     * @brief FPS is the framerate at which the slider is set to currently.
     * @return The desired framerate to play the animation.
     */
    int fps() const;

    /**
     * @brief Updates the framerate to the desired frequency.
     * @param The new framerate to play at.
     */
    void setFps(int value);

    /**
     * @brief Sets the number of frame buttons in the timeline.
     * Clears existing buttons and creates the specified number of new ones.
     * Use this when loading a new sprite to sync button count with frame count.
     * @param count The number of frames to display.
     */
    void setFrameCount(int count);

signals:
    /**
     * @brief Tells the controller that a frame at the index has been chosen.
     * @param The index of the chosen frame.
     */
    void frameSelected(int index);

    /**
     * @brief Tells the controller that a frame was added to the desired index.
     * @param The index to add the frame.
     */
    void frameAdded(int index);

    /**
     * @brief Tells the controller that a frame was removed from the desired index.
     * @param The index of the frame that was removed.
     */
    void frameRemoved(int index);

    /**
     * @brief Tells the controller that we want to change the framerate.
     * @param The new framerate value we should update to.
     */
    void fpsChanged(int fps);

private slots:
    /**
     * @brief Receives the signal from controller that a button image need to be updated.
     * Upon receiving the signal, the view draws the image drawn on the frame at index to a more current rendition.
     * @param index The index of the frame button to update
     * @param image The pixmap to display on the button
     */
    void updateButtonImage(int index, QPixmap image);

    /**
     * @brief Receives the signal from controller that a frame was selected.
     * Upon receiving the signal, the button is redrawn to the "selected" state from the stylesheet.
     */
    void onFrameClicked();

    /**
     * @brief Receives the signal from controller that a new frame has been added to the array of frames.
     * Upon receiving the signal, the UI is updated to show the new frame.
     */
    void onAddFrameClicked();

    /**
     * @brief Receives the signal from controller that a frame has been removed from the array, and that the timeline needs to update.
     * Upon receiving the signal, the the desired frame is removed from the UI.
     */
    void onRemoveFrameClicked();

    /**
     * @brief Receives the signal from controller that a new value for FPS has been selected through the scroll bar.
     * Upon receivng the signal, the FPS counter is redrawn to show the new value.
     * @param The new recorded FPS value.
     */
    void onFpsSliderChanged(int value);

private:
    /**
     * @brief Redraws the frames (which are buttons) to the "selected" style.
     */
    void updateFrameStyles();

    /**
     * @brief This is the UI element that the timeline belongs to.
     */
    Ui::Timeline *ui;

    /**
     * @brief The internal frame array that stores all the frames (which are buttons). This list is different from the array of frames
     * contained in the model, since these are QPushButtons rather than Frame objects.
     */
    QList<QPushButton*> frameButtons;

    /**
     * @brief The index of the selected frame. This tells the view which button the blue outline should be drawn upon.
     */
    int selectedIndex;

    /**
     * @brief The default size of the buttons in the timeline.
     */
    static const int FRAME_SIZE = 70;
};

#endif // TIMELINE_H
