#include "DBMS_UI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBMS_UI w;
    w.show();

    return a.exec();
}
