#ifndef TRIPPROGRESS_H
#define TRIPPROGRESS_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include "dbmanager.h"
#include "confirmpage.h"
#include "tripreceipt.h"



namespace Ui {
class tripprogress;
}

class tripprogress : public QDialog
{
    Q_OBJECT

public:


    explicit tripprogress(QWidget *parent = nullptr);


    ~tripprogress();

    QString tripID;


    QString currentCol;


    QString souvenirName;


    double souvenirPrice;

    int row;


    void displaySouv();

    void nextTrip();

    void getDistance();

    void updateCart();



    void updateTotal();

  public slots:

    void onLoadClick();

    void onNextClick();


    void onPrevClick();

private slots:
    void on_souvTable_clicked(const QModelIndex &index);

    void on_addCart_clicked();

    void on_pushButton_4_released();

    void on_removeCart_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:

    Ui::tripprogress *ui;


    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");


    QStringList trip;

    int counter;
    int max;
};

#endif // TRIPPROGRESS_H
