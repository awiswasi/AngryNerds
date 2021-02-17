#include "addsouvenir.h"

addSouvenir::addSouvenir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSouvenir)
{
    ui->setupUi(this);
    updateCombo();

}

addSouvenir::~addSouvenir()
{
    delete ui;
}

void addSouvenir::updateCombo()
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

void addSouvenir::on_pushButton_2_released()
{
    hide();
}

void addSouvenir::on_pushButton_released()
{
    confirmpage confirm;
    bool check = false;
    bool success = false;
    QString collegeName = ui->comboBox->currentText();


    if(ui->souEdit->text() == "")
    {
        ui->souEdit->setPlaceholderText("souvinir name empty!");
        success = true;
    }



}
