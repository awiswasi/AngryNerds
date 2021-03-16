#include "tripprogress.h"
#include "ui_tripprogress.h"

tripprogress::tripprogress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripprogress)
{
    ui->setupUi(this);
    counter = -1;

    myDb.resetCart();

}

tripprogress::~tripprogress()
{
    myDb.resetCart();

    delete ui;
}

void tripprogress::onLoadClick()
{
    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT college FROM Trips WHERE tripID = (:tripId)");
    qry->bindValue(":tripId" , tripID);

    trip.clear();

    if(!qry->exec())
    {
        qDebug() << "tripProgress initializeList query failed";


    }
    else
    {
        while(qry->next())
        {
                QString temp = qry->value("college").toString();
                trip << temp;
        }

    }
    qDebug() << trip;

    max = trip.size();

    nextTrip();

    this->ui->load->deleteLater();


    ui->removeCart->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
    ui->pushButton->setDisabled(false);


    getDistance();
}

void tripprogress::nextTrip()
{
    myDb.resetCart();
    updateCart();
    updateTotal();

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << counter;
    counter++;

    if( counter < max)
    {

         QString curCol;

         curCol = trip[counter];

         currentCol = trip[counter];

         this->ui->label->setText("You are at:  " + curCol);

         qry->prepare("SELECT souvenirName, cost FROM Souvenirs WHERE collegeName = (:collegeName)");
         qry->bindValue(":collegeName", curCol);

         if(qry->exec())
         {
             qDebug() << "souvenir table updated.";
         }

         model->setQuery(*qry);

         ui->souvTable->setModel(model);
         ui->souvTable->resizeColumnsToContents();

    }
    else
    {
        confirmpage confirm;
        bool check = false;

        confirm.setModal(true);
        confirm.exec();
        check = confirm.getData();

        if(check)
        {
            this->hide();
            tripReceipt *summary = new tripReceipt(tripID, this);

            summary->show();
        }
        else
        {
            counter--;
        }

    }

}



void tripprogress::getDistance()
{
    QString distance;

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT distanceToNext From Trips WHERE (college) = (:college)");
    qry->bindValue(":college", currentCol);

    if(qry->exec())
    {
        while(qry->next())
        {
            distance = qry->value(0).toString();
        }

        if(counter+1 < max)
            distance = "Distance to " + trip[counter+1] + ": " + distance;
        else
            distance = "You're at the last school!";

        ui->distanceLabel->setText(distance);
        qDebug() << distance;
        qDebug() << "show next college!";
    }
    else
        qDebug() << "doesn't show next colelge!";
}

void tripprogress::displaySouv()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT souvenirName FROM Souvenirs WHERE collegeName = (:startCollege)");
    qry->bindValue(":startCollege", currentCol);

    if(qry->exec())
    {
        qDebug() << "college table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->souvTable->setModel(model);
    ui->souvTable->setColumnWidth(20, 400);

}

void tripprogress::onNextClick()
{
    nextTrip();
    getDistance();
}

void tripprogress::onPrevClick()
{
   // prevTrip();
}

void tripprogress::on_pushButton_clicked()
{
   // onNextClick();
}
void tripprogress::updateCart()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT souvenir, quantity, total FROM Cart");

    if(qry->exec())
    {
        qDebug() << "college1 table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->cartTable->setModel(model);
}

void tripprogress::updateTotal()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT SUM(total) FROM Cart");

    if(qry->exec())
    {
        qDebug() << "college1 table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    model->setHeaderData(0, Qt::Horizontal, tr("Cart Total") );

}
void tripprogress::on_souvTable_clicked(const QModelIndex &index)
{

    if(index.isValid())
    {
        row = index.row();
        souvenirName = index.sibling(row, 0).data().toString();
        souvenirPrice = index.sibling(row, 1).data().toDouble();

        qDebug() << endl;

        qDebug() << tripID << " " << currentCol;
        qDebug() << souvenirName << " " << souvenirPrice;
        qDebug() << index;

    }

}

void tripprogress::on_addCart_clicked()
{
    int count = 1;
    int counter = myDb.cartQuantity(currentCol, souvenirName);

    if(counter == 0)
    {
        myDb.addCart(tripID,currentCol,souvenirName, souvenirPrice,count);
    }
    else
    {
        counter++;


        myDb.updateCart(currentCol,souvenirName,counter);
        qDebug() << counter;

    }
    updateTotal();
    updateCart();
}


void tripprogress::on_pushButton_4_released()
{
    confirmpage confirm;
    bool check;

    confirm.setModal(true);
    confirm.exec();
    check = confirm.getData();

    if(check)
    {
        myDb.addPurchase();
        myDb.resetCart();
    }
}

void tripprogress::on_pushButton_4_clicked()
{
qDebug() << endl;
}

void tripprogress::on_removeCart_clicked()
{
    myDb.removeCart(currentCol, souvenirName);
    updateCart();
    updateTotal();
}

void tripprogress::on_pushButton_3_clicked()
{
    int count = 1;
    int counter = myDb.cartQuantity(currentCol, souvenirName);

    if(counter == 0)
    {
        myDb.addCart(tripID,currentCol,souvenirName, souvenirPrice,count);
    }
    else
    {
        counter=ui->spinBox->value();
     myDb.updateCart(currentCol,souvenirName, counter);

     qDebug() << counter;

 }
 updateTotal();
 updateCart();
}
