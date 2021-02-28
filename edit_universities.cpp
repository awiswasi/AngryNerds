#include "edit_universities.h"
#include "ui_edit_universities.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

edit_universities::edit_universities(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_universities)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/sqlite3/initCampuses.db");

    mydb.open();
}

edit_universities::~edit_universities()
{
    delete ui;
}

//void edit_universities::on_pushButton_clicked()
//{
//    QString startingColleges=ui->startingColleges->text();
//    QString endingColleges=ui->endingColleges->text();
//    QString dist=ui->dist->text();

//    edit_universities obj;
//    QSqlQuery * qry=new QSqlQuery(obj.mydb);
//    qry->prepare("insert into initCampuses (startingColleges, endingColleges, dist) values ('"+startingColleges+"','"+endingColleges+"','"+dist+"')");
//}



void edit_universities::on_pushButton_edit_clicked()
{
    edit_universities obj;
    QString startingColleges, endingColleges, dist;
    startingColleges =ui->startingColleges_txt->text();
    endingColleges =ui->endingColleges_txt->text();
    dist =ui->dist_txt->text();

    mydb.open();
    QSqlQuery * qry=new QSqlQuery(obj.mydb);
    qry->prepare("insert into initCampuses(startingColleges, endingColleges, dist) values ('"+startingColleges+"', '"+endingColleges+"', '"+dist+"')");

    if(qry->exec())
    {
        QMessageBox::critical(this,tr("Save"), tr("Saved"));
    }
    else
    {
        //QMessageBox::critical(this,tr("error::"), qry.lastError().text());
    }
}

void edit_universities::on_displayButton_clicked()
{
    edit_universities obj;
    QSqlQueryModel * model=new QSqlQueryModel();

    QSqlQuery * qry=new QSqlQuery(obj.mydb);
    qry->prepare("select startingColleges, endingColleges, dist from initCampuses");

    qry->exec();
    model->setQuery(*qry);
    ui->editTable->setModel(model);
}
