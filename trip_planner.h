#ifndef TRIP_PLANNER_H
#define TRIP_PLANNER_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "display_colleges.h"
#include <qcheckbox.h>

namespace Ui {
class trip_planner;
}

class trip_planner : public QDialog
{
    Q_OBJECT

public:
    explicit trip_planner(QWidget *parent = nullptr);
    ~trip_planner();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
   // void updateCollegeTable(QString colName);

private:

    Ui::trip_planner *ui;
    display_colleges *displayColleges;

     QStringList selectedColleges;
     QString colName;

     //  int distance;

      // QString id;

     //  QList<int> distanceTo;
};

#endif // TRIP_PLANNER_H
