#ifndef DBMS_UI_H
#define DBMS_UI_H

#include <QMainWindow>
#include "MiniSQL_ABC.h"        // in order to list table_name,index_name,etc

namespace Ui {
class DBMS_UI;
}

class DBMS_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBMS_UI(QWidget *parent = 0);
    ~DBMS_UI();

private:
    Ui::MainWindow *ui;
};

#endif // DBMS_UI_H
