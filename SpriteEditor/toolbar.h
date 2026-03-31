#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class toolbar;
}

/**
 * @brief The toolbar class provides a toolbar menu for the canvas widget to change the current selected brush/tool.
 *
 * The toolbar uses buttons signals to change the current brush/tool within the controller.
 */
class toolbar : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the toolbar widget.
     * @param parent widget
     */
    explicit toolbar(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the toolbar widget.
     */
    ~toolbar();


signals:
    /**
     * @brief standardBrushSelectedSignal sends signal to controller to update current brush/tool to standard brush.
     */
    void standardBrushSelectedSignal();

    /**
     * @brief eraserToolSelectedSignal sends signal to controller to update current brush/tool to eraser tool.
     */
    void eraserToolSelectedSignal();

    /**
     * @brief paintBucketSelectedSignal sends signal to controller to update current brush/tool to paint bucket tool.
     */
    void paintBucketSelectedSignal();

    /**
     * @brief eyeDropperToolSelectedSignal sends signal to controller to update current brush/tool to eyedropper tool.
     */
    void eyeDropperToolSelectedSignal();

    /**
     * @brief mirrorToolSelectedSignal sends signal to controller to update current brush/tool to mirror tool.
     */
    void mirrorToolSelectedSignal();

    /**
     * @brief selectionToolSelectedSignal sends signal to controller to update current brush/tool to selection tool.
     */
    void selectionToolSelectedSignal();

private slots:

    /**
     * @brief on_PaintBrush_clicked recieves a signal from PaintBrush's QPushButton::clicked
     * then emits the standardBrushSelectedSignal to the controller.
     */
    void on_PaintBrush_clicked();

    /**
     * @brief on_Eraser_clicked recieves a signal from Eraser_clicked's QPushButton::clicked
     * then emits the eraserToolSelectedSignal to the controller.
     */
    void on_Eraser_clicked();

    /**
     * @brief on_FillBucket_clicked recieves a signal from FillBucket's QPushButton::clicked
     * then emits the eraserToolSelectedSignal to the controller.
     */
    void on_FillBucket_clicked();

    /**
     * @brief on_EyeDropper_clicked recieves a signal from EyeDropper's QPushButton::clicked
     * then emits the EyeDropperToolSelectedSignal to the controller.
     */
    void on_EyeDropper_clicked();

    /**
     * @brief on_Mirror_clicked recieves a signal from Mirror's QPushButton::clicked
     * then emits the mirrorToolSelectedSignal to the controller.
     */
    void on_Mirror_clicked();

    /**
     * @brief on_Selection_clicked recieves a signal from Selection's QPushButton::clicked
     * then emits the selectionToolSelectedSignal to the controller.
     */
    void on_Selection_clicked();

private:
    Ui::toolbar *ui;
};

#endif // TOOLBAR_H
