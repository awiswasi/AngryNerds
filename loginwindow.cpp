#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "dbmanager.h"
#include "tripplanner.h"
#include "loginpage.h"
#include "display.h"
#include <QMessageBox>


LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    myDb.createTripTable();

    if(!myDb.isOpen())
    {
        ui->dbStatus->setText("Failed to open database!");
    }
    else
    {
        ui->dbStatus->setText("Connected");
    }
    QPixmap pix(PROJECT_PATH + "/logo.png");

    ui->label_2->setPixmap(pix);


}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::onPlanClick()
{
    this->hide();
    tripPlanner *planner = new tripPlanner(this);
    planner->show();
}




void LoginWindow::on_pushButton_clicked()
{
    this->hide();
   loginPage *login = new loginPage(this);
    login->show();
}

void LoginWindow::on_pushButton_2_clicked()
{
    display *dis = new display(this);
     dis->show();
}
