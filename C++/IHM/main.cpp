#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Instanciate application
    QApplication app(argc, argv);
    MainWindow window;

    // Display
    window.show();

    // Execute
    return app.exec();
}
