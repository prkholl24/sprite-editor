#include "mainwindow.h"

#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
  //  QString text = QInputDialog::getText(nullptr, "New Srite Wizard", "Please enter the resolution", QLineEdit::Normal);
    return a.exec();
}
