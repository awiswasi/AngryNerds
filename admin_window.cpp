#include "admin_window.h"
#include "ui_admin_window.h"
#include "edit_universities.h"

admin_window::admin_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_window)
{
    ui->setupUi(this);
}

admin_window::~admin_window()
{
    delete ui;
}

void admin_window::on_pushButton_clicked()
{
    editUni = new edit_universities(this);
    editUni->show();
}
