#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;  // Créez une instance de votre fenêtre principale
    mainWindow.show();      // Affichez la fenêtre principale
    return app.exec();
}
