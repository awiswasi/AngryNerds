#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>

loginPage::loginPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginPage)
{
    ui->setupUi(this);


   // myDb.createTripTable();

}

loginPage::~loginPage()
{
    delete ui;
}

void loginPage::on_pushButton_clicked()
{
    QString passWord;
    QString userName;

    userName = this->ui->lineEdit->text();
    passWord = this->ui->lineEdit_2->text();


    if(passWord == myDb.getPassword(userName))
    {
        if(myDb.checkAdmin(userName))
        {
            this->hide();
            admin = new AdminWindow(this);
            admin->show();
        }
        else
        {

            qDebug() << "User login succuss";
            this->hide();
            tripPlanner *planner = new tripPlanner(this);
            planner->show();
        }
    }
    else
    {
        QMessageBox::information(this,"title","wrong info");
    }
}

void loginPage::on_pushButton_3_clicked()
{

    QString passWord;
    QString userName;

    userName = this->ui->lineEdit->text();
    passWord = this->ui->lineEdit_2->text();


    if(userName != "" && passWord!= "")
    {
        myDb.addUser(userName, passWord);
        this->hide();

    }
}

void loginPage::on_pushButton_2_clicked()
{
    this->ui->lineEdit->setText("");
    this->ui->lineEdit_2->setText("");

}
