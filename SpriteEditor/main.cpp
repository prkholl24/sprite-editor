/**
 * @file main.cpp
 * @brief main is called upon execution
 *
 * Initializes the application
 *
 * Team: Green Goombas
 * github url: https://github.com/UofU-CS3505/cs3505-assignment8-GreenGoombas.git
 * @authors Charles Adair, Armando Carrillo, Parker Hollingsed,
 *          Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3/29/2026
 *
 * Last Revision: 3/30/2026 10:40PM MST by Lindsey Reese
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
