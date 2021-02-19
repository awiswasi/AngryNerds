#include "edit_universities.h"
#include "ui_edit_universities.h"

edit_universities::edit_universities(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_universities)
{
    ui->setupUi(this);
}

edit_universities::~edit_universities()
{
    delete ui;
}
