#include "mainwindow.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//operation - не работает
