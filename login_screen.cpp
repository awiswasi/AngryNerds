#include "login_screen.h"
#include "ui_login_screen.h"
#include <QMessageBox>
#include "admin_window.h"



login_screen::login_screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_screen)
{
    ui->setupUi(this);
}

login_screen::~login_screen()
{
    delete ui;
}

void login_screen::on_pushButton_Login_clicked()
{
    QString userName = ui->userName->text();
    QString passWord = ui->passWord->text();

    if(userName == "snoopDogg" && passWord == "D oh double G")
    {
        QMessageBox::information(this, "Login", "Username and Password is correct");
        admin = new admin_window(this);
        admin->show();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username and Password is not correct");
    }

}
