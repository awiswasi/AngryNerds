#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>
#include <QList>
#include "dbmanager.h"
#include <qcheckbox.h>
#include "tripreceipt.h"
#include "tripprogress.h"
#include <QDialog>

namespace Ui {
class display;
}

class display : public QDialog
{
    Q_OBJECT

public:
    explicit display(QWidget *parent = nullptr);
    ~display();
   void  updateCollegeTable(QString start);
   void updateSouvTable(QString start);
   void updateCombo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::display *ui;

    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");


    QVector<QCheckBox*> checkBoxVector;


    QStringList selectedColleges; // a string to hold the selected colleges - should be helpful for the plan trip algorithm


    QStringList plannedColleges;


    int distance;


    QString id;

    QList<int> distanceTo;

    tripprogress *progress;
};

#endif // DISPLAY_H
