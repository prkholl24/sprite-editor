/**
 * @file main.cpp
 * @brief main is called upon execution
 *
 * Initializes the application
 *
 * @authors Charles Adair, Armando Carrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/29/2026
 *
 * Last Revision: 3/29/2026 12:46AM MST by Charles Adair
 */
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
  //  QString text = QInputDialog::getText(nullptr, "New Srite Wizard", "Please enter the resolution", QLineEdit::Normal);
    return a.exec();
}
