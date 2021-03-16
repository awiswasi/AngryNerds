#include "confirmpage.h"
#include "ui_confirmpage.h"
#include "dbmanager.h"

confirmpage::confirmpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmpage)
{
    ui->setupUi(this);

    QPixmap pix(PROJECT_PATH + "/confirm.png");

    ui->label->setPixmap(pix);
}

confirmpage::~confirmpage()
{
    delete ui;
}

bool confirmpage::getData()
{
    qDebug() << "getData()";
    return answer;
}

void confirmpage::on_okButton_released()
{
    answer = true;
    hide();
}

void confirmpage::on_cancelButton_released()
{
    answer = false;
    hide();
}



