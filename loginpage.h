#ifndef LOGINPAGE_H
#define LOGINPAGE_H


#include <QMainWindow>
#include "dbmanager.h"
#include "adminwindow.h"
#include "tripplanner.h"

#include <QPixmap>
#include <QDialog>

namespace Ui {
class loginPage;
}

class loginPage : public QDialog
{
    Q_OBJECT

public:
    explicit loginPage(QWidget *parent = nullptr);
    ~loginPage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::loginPage *ui;

    DbManager myDb = DbManager( PROJECT_PATH + "/college.db");


    AdminWindow *admin;
};

#endif // LOGINPAGE_H
