#include "display.h"
#include "ui_display.h"

display::display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::display)
{
    ui->setupUi(this);
    updateCombo();
}

display::~display()
{
    delete ui;
}

void display::on_pushButton_clicked()
{
    QString startingCollege;
    startingCollege = this->ui->comboBox->currentText();

     updateCollegeTable(startingCollege);
     updateSouvTable(startingCollege);

}

void display::updateCollegeTable(QString start)
{
    this->ui->collegeLabel->setText("College distances from: " + start);
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT endCollege, distance FROM Distances WHERE startCollege = (:startCollege)");
    qry->bindValue(":startCollege", start);

    if(qry->exec())
    {
        qDebug() << "college table updated.";
    }

    model->setQuery(*qry);

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void display::updateCombo()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT DISTINCT startCollege FROM Distances");

    if(qry->exec())
    {
        qDebug() << "college1 table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->comboBox->setModel(model);
}

void display::updateSouvTable(QString start)
{
    this->ui->label->setText("Souvenirs at: " + start);
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT souvenirName, cost FROM Souvenirs WHERE collegeName = (:startCollege)");
    qry->bindValue(":startCollege", start);

    if(qry->exec())
    {
        qDebug() << "college table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();

}
