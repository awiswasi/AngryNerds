#include "college_tour.h"
#include "ui_collegetour.h"
#include "display_colleges.h"
#include "admin_window.h"

CollegeTour::CollegeTour(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::CollegeTour)
{
    ui->setupUi(this);
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/sqlite3/campuses.db");

    if(!mydb.open())
    {
        ui->label->setText("stupidA$$ hoez");
    }
    else
    {
        ui->label->setText("you in dogg");
    }
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

void CollegeTour::on_pushButton_2_clicked()
{
    loginScreen = new login_screen(this);
    loginScreen->show();

}
