#ifndef TRIP_PLANNER_H
#define TRIP_PLANNER_H

#include "DBManager.h"
#include "admin_window.h"
#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "display_colleges.h"
#include <qcheckbox.h>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include "customtrip.h"

namespace Ui {
class trip_planner;
}

class trip_planner : public QDialog
{
    Q_OBJECT

public:
    explicit trip_planner(QWidget *parent = nullptr);
    ~trip_planner();

   // void updateCollegeTable(QString colName);

private slots:
    void on_add_button_clicked();


private:

    Ui::trip_planner *ui;
    display_colleges *displayColleges;
    customTrip *customTrip;

    bool checked;

QString op1 ="Starting from UCI";
QString op2 ="Starting from ASU";
QString custom = "Create your own trip";

     //  int distance;
    DBManager mydb;

     //  QList<int> distanceTo;
};

#endif // TRIP_PLANNER_H
