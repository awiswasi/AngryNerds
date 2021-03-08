#include "edit_souvenirs.h"
#include "ui_edit_souvenirs.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

edit_souvenirs::edit_souvenirs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_souvenirs)
{
    ui->setupUi(this);

    QSqlDatabase souvdb = QSqlDatabase::addDatabase("QSQLITE");
    souvdb.setDatabaseName("C:/sqlite3/souvenirs.db");

    souvdb.open();
}

edit_souvenirs::~edit_souvenirs()
{
    delete ui;
}

void edit_souvenirs::on_pushButton_3_clicked()
{

}

//DISPLAY SOUVENIRS
void edit_souvenirs::on_displaySouvenirsButton_clicked()
{
    edit_souvenirs obj;
    QSqlQueryModel * model=new QSqlQueryModel();

    QSqlQuery * qry=new QSqlQuery(obj.souvdb);
    qry->prepare("select colleges, traditionalSouvenirs, cost from souvenirs");

    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
}

// ADD SOUVENIRS
void edit_souvenirs::on_pushButton_clicked()
{
    edit_souvenirs obj;
    QString colleges, traditionalSouvenirs, cost;
    colleges =ui->colleges_txt->text();
    traditionalSouvenirs =ui->traditionalSouvenirs_txt->text();
    cost =ui->cost_txt->text();

    souvdb.open();
    QSqlQuery * qry=new QSqlQuery(obj.souvdb);
    qry->prepare("insert into souvenirs(colleges, traditionalSouvenirs, cost) values ('"+colleges+"', '"+traditionalSouvenirs+"', '"+cost+"')");

    if(qry->exec())
    {
        QMessageBox::critical(this,tr("Save"), tr("Saved"));
    }
    else
    {
        //QMessageBox::critical(this,tr("error::"), qry.lastError().text());
    }
}

// DELETE SOUVENIRS
void edit_souvenirs::on_pushButton_4_clicked()
{
    QSqlQuery qry;

        QString deleteSouvenir;
        deleteSouvenir=ui->deleteSouvenir_txt->text();

        qry.prepare("Delete from souvenirs where traditionalSouvenirs = '"+deleteSouvenir+"'");

        if(qry.exec())
        {
            QMessageBox::critical(this, tr("Delete"), tr("Deleted"));
        }
        else
        {
            //QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }
}

// EDIT SOUVENIRS
void edit_souvenirs::on_pushButton_2_clicked()
{
        /*QSqlQuery qry;

        QString colleges, traditionalSouvenirs, cost;
        colleges=ui->editColleges_txt->text();
        traditionalSouvenirs=ui->editSouvenirs_txt->text();
        cost=ui->editCost_txt->text();

        qry.prepare("update customers set colleges = '"+colleges+"', traditionalSouvenirs = '"+traditionalSouvenirs+"', cost = '"+cost+"'");

        if(qry.exec())
        {
            QMessageBox::critical(this, tr("Edit"), tr("Updated"));
        }
        else
        {
            //QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }*/
}

// SEARCH SOUVENIRS
void edit_souvenirs::on_searchSouvenirButton_clicked()
{
    QString searchSouvenirs;
    searchSouvenirs=ui->searchSouvenirs_txt->text();

    edit_souvenirs obj;
    QSqlQueryModel * model=new QSqlQueryModel();

    QSqlQuery * qry=new QSqlQuery(obj.souvdb);

    qry->prepare("select colleges, traditionalSouvenirs, cost from souvenirs WHERE traditionalSouvenirs = '"+searchSouvenirs+"'");

    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
}
