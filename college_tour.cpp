#include "college_tour.h"
#include "ui_collegetour.h"
#include "display_colleges.h"
#include "admin_window.h"

CollegeTour::CollegeTour(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::CollegeTour)
{
    ui->setupUi(this);

}

CollegeTour::~CollegeTour()
{
    delete ui;
}


void CollegeTour::on_displayCollegeButton_clicked()
{
//    display_colleges displayColleges;
//    displayColleges.setModal(true);
//    displayColleges.exec();
    displayColleges = new display_colleges(this);
    displayColleges->show();

}

void CollegeTour::on_planYourTripButton_clicked()
{
    planTrip = new trip_planner(this);
    planTrip->show();

}

void CollegeTour::on_pushButton_2_clicked()
{
    loginScreen = new login_screen(this);
    loginScreen->show();

}
