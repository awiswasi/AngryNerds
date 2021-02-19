#include "edit_souvenirs.h"
#include "ui_edit_souvenirs.h"

edit_souvenirs::edit_souvenirs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_souvenirs)
{
    ui->setupUi(this);
}

edit_souvenirs::~edit_souvenirs()
{
    delete ui;
}
