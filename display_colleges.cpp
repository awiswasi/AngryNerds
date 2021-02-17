#include "display_colleges.h"
#include "ui_display_colleges.h"

display_colleges::display_colleges(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::display_colleges)
{
    ui->setupUi(this);
}

display_colleges::~display_colleges()
{
    delete ui;
}
