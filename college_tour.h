#ifndef COLLEGETOUR_H
#define COLLEGETOUR_H


#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "display_colleges.h"
#include "login_screen.h"
#include "trip_planner.h"
#include "admin_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CollegeTour; }
QT_END_NAMESPACE

class CollegeTour : public QMainWindow
{
    Q_OBJECT

public:
    CollegeTour(QWidget *parent = nullptr);
    ~CollegeTour();

private slots:
    void on_displayCollegeButton_clicked();

    void on_pushButton_2_clicked();
    void on_planYourTripButton_clicked();

private:
    Ui::CollegeTour *ui;
    display_colleges *displayColleges;
    login_screen *loginScreen;
    admin_window *admin;
    trip_planner *planTrip;
};
#endif // COLLEGETOUR_H
