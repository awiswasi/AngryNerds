#include "customtrip.h"
#include "ui_customtrip.h"

customTrip::customTrip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customTrip)
{
    ui->setupUi(this);
}

customTrip::~customTrip()
{
    delete ui;
}

void customTrip::on_pushButton_clicked()
{
        start = ui->lineEdit->text();

    ui->listWidget->addItem(start);
}







void customTrip::on_pushButton_2_clicked()
{
 static QString other;
 bool check = false;
 static QString name;

    other = ui->lineEdit_2->text();

         ui->listWidget_2->addItem(other);

        // otherCollege[0]= other;
/*
if(!(name == other))
{
     otherCollege[1]= other;
}


for (int i=0; i<2;i++ )
{
ui->listWidget_2->addItem(otherCollege[i]);
}
*/

}

void customTrip::on_pushButton_3_clicked()
{
    progress = new class trip_progress(this);
    progress->show();
}
