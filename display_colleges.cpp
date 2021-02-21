#include "display_colleges.h"
#include "ui_display_colleges.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

display_colleges::display_colleges(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::display_colleges)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/sqlite3/displayCampuses.db");

    mydb.open();
}

display_colleges::~display_colleges()
{
    delete ui;
}

void display_colleges::on_pushButton_clicked()
{
    display_colleges obj;
    QSqlQueryModel * model=new QSqlQueryModel();

    QSqlQuery * qry=new QSqlQuery(obj.mydb);
    //qry->prepare("select MIN(startingColleges) AS startingColleges, dist from initCampuses group by startingColleges");
    qry->prepare("select campusName, distance from displayCampuses");

    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
}
