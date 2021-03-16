#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QDialog>
#include <QList>
#include "dbmanager.h"
#include <qcheckbox.h>
#include "tripreceipt.h"
#include "tripprogress.h"



namespace Ui {
class tripPlanner;
}

class tripPlanner : public QDialog
{
    Q_OBJECT

public:

    explicit tripPlanner(QWidget *parent = nullptr);


    ~tripPlanner();


    void initializeList();

    void selectedCollegeList();


    void planAlgorithm(QString start, int dist);


    bool collegeDoesExist(QString colName);


    bool planDoesExist(QString colName);


    void showTrip(QString ID);

    void updateCombo();


private slots:

    void ChecboxChanged();


    void onPlanClick();


    void onDisplayClick();
    void onStartClick();

private:

    Ui::tripPlanner *ui;


    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");


    QVector<QCheckBox*> checkBoxVector;


    QStringList selectedColleges; // a string to hold the selected colleges


    QStringList plannedColleges;


    int distance;

    QString id;

    QList<int> distanceTo;

    tripprogress *progress;


};

#endif // TRIPPLANNER_H
