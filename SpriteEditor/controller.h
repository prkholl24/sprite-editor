#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "sprite.h"
// #include "toolbar.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief model is the current Sprite object being edited
     *
     * Model object starts uninitialized.
     */
    Sprite* model = nullptr;

    enum class ToolStates {StandardBrush, PaintBucket, Eraser, Eyedropper, Mirror, SelectionTool};
    ToolStates currentTool;


    void fillBucket(int x, int y);
public:
    /**
     * @brief Controller constructor
     *
     * Creates a new controller object with no model initialized.
     * On initialization this Controller waits for a signal from the
     * "New" or "Load" buttons in order to create the Sprite object
     * to manipulate
     */
    Controller(QWidget *parent = nullptr);
signals:

public slots:


    void newProjectSlot(int spriteSize);

    void toolBarEraserClicked();

    void handleCanvasInputSlot(int x, int y);

};

#endif // CONTROLLER_H
