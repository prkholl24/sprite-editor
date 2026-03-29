#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class toolbar;
}

class toolbar : public QWidget
{
    Q_OBJECT

public:
    explicit toolbar(QWidget *parent = nullptr);
    ~toolbar();


signals:

    void eraserClickedSignal();

private slots:
    void on_PaintBrush_clicked();

    void on_Eraser_clicked();

    void on_FillBucket_clicked();

    void on_EyeDropper_clicked();

    void on_Mirror_clicked();

    void on_Selection_clicked();

private:
    Ui::toolbar *ui;
};

#endif // TOOLBAR_H
