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

signals:

    /**
     * @brief Notifies the Controller that a new Sprite Project is being created and to initialize a new Sprite object
     * @param Sprite size
     */
    void newProjectSignal(int spriteSize);

    /**
     * @brief Notifies the Controller that a pre-existing Sprite Project is being loaded into the program.
     * @param existing Sprite file
     */
    void loadProjectSignal(QString filePath);

    /**
     * @brief Notifies the Controller to save the current Sprite Project into a Sprite file.
     * @param file path to save sprite
     */
    void saveProjectSignal(QString filePath);

    /**
     * @brief Notifies the Controller of user input to Canvas.
     * @param user mouseclick's x coordinate
     * @param user mouseClick's y coordinate
     */
    void canvasInput(int x, int y);

private slots:

    /**
     * @brief emits a signal to Controller to save a Sprite
     */
    void on_actionSave_triggered();

    /**
     * @brief emits a signal to Controller to create a new Sprite
     */
    void on_actionNew_triggered();

    /**
     * @brief emits a signal to Controller to load a Sprite
     */
    void on_actionLoad_triggered();

private:
    Ui::MainWindow *ui;

    Controller* control = nullptr;


};
#endif // MAINWINDOW_H
