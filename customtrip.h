#ifndef CUSTOMTRIP_H
#define CUSTOMTRIP_H

#include <QDialog>
#include <QSqlQuery>
#include <QTableView>
#include <QMessageBox>
#include <QLineEdit>
#include <QListWidget>
#include "trip_progress.h"

const int SIZE = 5;
namespace Ui {
class customTrip;
}

class customTrip : public QDialog
{
    Q_OBJECT

public:
    explicit customTrip(QWidget *parent = nullptr);
    ~customTrip();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::customTrip *ui;
    QString start;
 QString otherCollege[SIZE];
 trip_progress *progress;

};

#endif // CUSTOMTRIP_H
