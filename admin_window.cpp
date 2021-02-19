#include "admin_window.h"
#include "ui_admin_window.h"

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
