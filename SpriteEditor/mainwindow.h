#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//public slots: void openFile();

signals:

    /*
     *
     */
    void newProject(int spriteSize);



    void canvasInput(int x, int y);

    void fillBucketSelected();

private slots:
    void on_actionSave_triggered();

    void on_actionNew_triggered();

    void on_pushButton_clicked();

    void on_fillBucket_clicked();

private:
    Ui::MainWindow *ui;

    Controller* control = nullptr;


};
#endif // MAINWINDOW_H
