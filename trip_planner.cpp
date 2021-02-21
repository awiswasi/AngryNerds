#include "trip_planner.h"
#include "ui_trip_planner.h"

trip_planner::trip_planner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trip_planner)
{
    ui->setupUi(this);
}

trip_planner::~trip_planner()
{
    delete ui;
}

void trip_planner::on_pushButton_clicked()
{

    displayColleges = new display_colleges(this);
    displayColleges->show();

}

/*
void trip_planner::on_pushButton_2_clicked()
{
    QString startingCollege;
    startingCollege = this->ui->colName->currentText();
}


void trip_planner::updateCollegeTable(QString colName)
{


}
*/
