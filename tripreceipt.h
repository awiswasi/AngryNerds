

#ifndef TRIPRECEIPT_H
#define TRIPRECEIPT_H

#include <QDialog>
#include "dbmanager.h"



namespace Ui {
class tripReceipt;
}

class tripReceipt : public QDialog
{
    Q_OBJECT

public:

    explicit tripReceipt(QWidget *parent = nullptr);


    explicit tripReceipt(const QString& id, QWidget *parent = nullptr);


    ~tripReceipt();



private slots:

    void on_school_comboBox_currentIndexChanged(const QString &arg1);


    void updateTripSchoolList();

    void updateSchoolComboBox();

    void updateTotalDistance();

    void updateSchoolTotal();

    void updateTripTotal();

private:

    Ui::tripReceipt *ui;


    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");

    QString tripID;
};

#endif // TRIPRECEIPT_H
