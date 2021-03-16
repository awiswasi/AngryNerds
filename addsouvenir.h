#ifndef ADDSOUVENIR_H
#define ADDSOUVENIR_H

#include <QDialog>
#include "dbmanager.h"
#include "confirmpage.h"

namespace Ui {
class addSouvenir;
}

class addSouvenir : public QDialog
{
    Q_OBJECT

public:

    explicit addSouvenir(QWidget *parent = nullptr);


    ~addSouvenir();


    void updateCombo();

private slots:
    void on_pushButton_2_released();


    void on_pushButton_released();


private:

    Ui::addSouvenir *ui;


    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");


};

#endif // ADDSOUVENIR_H
