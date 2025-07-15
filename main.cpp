#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// #include <QApplication>
// #include <QLabel>

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);
    
//     QLabel label("Тест: Qt работает!");
//     label.resize(400, 300);
//     label.show();
    
//     return app.exec();
// }