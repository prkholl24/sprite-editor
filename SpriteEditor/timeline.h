#ifndef TIMELINE_H
#define TIMELINE_H

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
    explicit Timeline(QWidget *parent = nullptr);
    ~Timeline();

    void addFrame();

    void removeFrame(int index);

    int frameCount() const;

    int selectedFrame() const;

    void selectFrame(int index);

    int fps() const;

    void setFps(int value);

signals:
    void frameSelected(int index);

    void frameAdded(int index);

    void frameRemoved(int index);

    void fpsChanged(int fps);

private slots:
    void onFrameClicked();
    void onAddFrameClicked();
    void onRemoveFrameClicked();
    void onFpsSliderChanged(int value);

private:
    void updateFrameStyles();

    Ui::Timeline *ui;
    QList<QPushButton*> frameButtons;
    int selectedIndex;

    static const int FRAME_SIZE = 100;
};

#endif // TIMELINE_H
