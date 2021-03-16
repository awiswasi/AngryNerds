#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include "adminwindow.h"
#include "tripplanner.h"

#include <QPixmap>


QT_BEGIN_NAMESPACE

namespace Ui
{
class LoginWindow;
  }

QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public slots:

    void onPlanClick();

public:

    LoginWindow(QWidget *parent = nullptr);


    ~LoginWindow();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::LoginWindow *ui;


    DbManager myDb = DbManager(PROJECT_PATH+ "/college.db");


    AdminWindow *admin;

};
#endif // LOGINWINDOW_H
