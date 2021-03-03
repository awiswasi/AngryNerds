#include "trip_planner.h"
#include "ui_trip_planner.h"
#include "display_colleges.h"
#include "college_tour.h"
#include <QSqlQuery>
#include <QTableView>
#include <QMessageBox>
#include <QLineEdit>

trip_planner::trip_planner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trip_planner)
{
    ui->setupUi(this);
    ui->comboBox->addItem(op1);
    ui->comboBox->addItem(op2);


    ui->comboBox->addItem(custom);
}

trip_planner::~trip_planner()
{
    delete ui;


}



/*
void trip_planner::on_add_button_clicked()
{

    if(comboBox == "Starting from UCI")
    {

    }
    else
    {

    }

    //QTableView::setModel(Model);
}
*/
void trip_planner::on_add_button_clicked()
{

    // bool checked;
    QString comboBox = ui->comboBox->currentText();
    // checked  = planDoesExist(comboBox);



    if (comboBox == op1)
    {
        QMessageBox::information(this,"title",ui->comboBox->currentText());
        //ui->comboBox->currentText()
    }
else

        if (comboBox == op2)

        {
        QMessageBox::information(this,"title","");
        //ui->comboBox->currentText()

        }
else
     if (comboBox == custom)

        {

   // QMessageBox::information(this,"title","Choose from one of the displaying colleges and enter the name in the box down below.");

         customTrip = new class customTrip(this);
         customTrip->show();

        }
}


/*
void trip_planner::on_Enter_clicked()
{





     bool truth = false;
     QString customTrip = ui->lineEdit->text();
      truth = mydb.verifyName(customTrip) ;
if(truth == true)
{
      QMessageBox::information(this,"title",customTrip);

}
else
{
      QMessageBox::information(this,"title","nope");
}

}
*/
