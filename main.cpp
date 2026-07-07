#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Векторный редактор — Шаг 2");
    window.show();

    return app.exec();
}