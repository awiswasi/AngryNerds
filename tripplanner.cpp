#include "tripplanner.h"
#include "ui_tripplanner.h"
#include <QMessageBox>
#include "QVBoxLayout"
#include "adminwindow.h"

tripPlanner::tripPlanner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripPlanner)
{
    ui->setupUi(this);


    initializeList();
    updateCombo();
    this->ui->typeName->addItem("custom");
    this->ui->typeName->addItem("auto");
}

tripPlanner::~tripPlanner()
{
    delete ui;
}

void tripPlanner::updateCombo()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT DISTINCT startCollege FROM Distances");

    if(qry->exec())
    {
        qDebug() << "college1 table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->colName->setModel(model);
}


void tripPlanner::initializeList()
{
    QSqlQuery *query = new QSqlQuery();

    checkBoxVector.clear();

    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->CollegeList_scrollArea->setWidget(container);



    query->prepare("SELECT DISTINCT startCollege FROM Distances");
    if(!query->exec())
    {
        qDebug() << "tripPlanner initializeList query failed";


    }
    else
    {
        while(query->next())
        {
            QCheckBox* checkBox = new QCheckBox(query->value(0).toString());
            checkBox->setCheckState(Qt::CheckState::Unchecked);
            checkBoxVector.push_back(checkBox);
            connect(checkBox, &QCheckBox::stateChanged, this, &tripPlanner::CheckboxChanged);
        }

        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            vBoxLayout->addWidget(checkBoxVector[i]);
        }
    }
}

void tripPlanner::CheckboxChanged()
{

    qDebug() << "Signal caught";

    int checkedCount = 0;

    for(int i = 0; i < checkBoxVector.size(); i++)
    {
        if(checkBoxVector[i]->checkState() == Qt::CheckState::Checked)
        {
            checkedCount++;
        }
    }

    if(checkedCount == 13)
    {
        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            if(checkBoxVector[i]->checkState() == Qt::CheckState::Unchecked)
            {
                checkBoxVector[i]->setDisabled(true);
            }
            qDebug() << checkBoxVector[i] << endl;
        }
    }

    else
    {
        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            checkBoxVector[i]->setDisabled(false);
        }
    }

}

void tripPlanner::selectedCollegeList()
{
    selectedColleges.clear();
    QSqlQuery *query = new QSqlQuery();
    int i = 0;

    query->prepare("SELECT DISTINCT startCollege FROM Distances");
    if(!query->exec())
    {
        qDebug() << "tripPlanner initializeList query failed";


    }
    else
    {
        while(query->next())
        {
             if(checkBoxVector[i]->checkState() == Qt::CheckState::Checked)
            {
                QString temp = query->value("startCollege").toString();
                selectedColleges << temp;
                qDebug()<< temp << endl;

            }
            i++;
        }

    }
}

void tripPlanner::onPlanClick()
{
    distance = 0;
    QString startingCollege,type;
    QString tripID;
    startingCollege = this->ui->colName->currentText();
    type = this->ui->typeName->currentText();
    tripID = this->ui->trip->text();

    int stops;
    stops= ui->spinBox->value();

    if(startingCollege =="University of California, Irvine (UCI)" && type =="auto")
    {
    prePlanned();
    }
     else if(startingCollege =="Arizona State University" && type == "auto")
    {
    prePlanned();
    }
    else
    {
    selectedCollegeList();
    }

    if(!collegeDoesExist(startingCollege))
    {
        QMessageBox::information(this,"title","Select colleges from the right coloumn =>");
    }
    else
    {

        qDebug() << myDb.tripIdExists(tripID);
        if((tripID.size()>0 && tripID.size()<4 && !myDb.tripIdExists(tripID)))
        {
          //  this->ui->warningLabel->setText("");
           // this->ui->tripWarning->setText("");
            plannedColleges.clear();
            planAlgorithm(startingCollege, distance); // will plan the trip
            distanceTo << 0; // adds 0 for distance to next college at last college
            if(startingCollege =="University of California, Irvine (UCI)" && type =="auto")
            {
            for(int index = 0; index < plannedColleges.size()-(12-(stops+1)+1); index++)
            {
                myDb.addTrip(tripID, plannedColleges[index], index, distanceTo[index]); // uploads trip to DB
            }
            }
            else if(startingCollege =="Arizona State University" && type == "auto")
            {
                for(int index = 0; index < plannedColleges.size()-(12-(stops+1)+1); index++)
                {
                    myDb.addTrip(tripID, plannedColleges[index], index, distanceTo[index]); // uploads trip to DB
                }

            }
            else
            {
                for(int index = 0; index < plannedColleges.size(); index++)
                {
                    myDb.addTrip(tripID, plannedColleges[index], index, distanceTo[index]); // uploads trip to DB
                }
            }
            showTrip(tripID);
            id = tripID;

            QString out = QString::number(distance);
            this->ui->dist->setText(out);

        }
        else
        {

            QMessageBox::information(this,"title","This trip number has already been registered");
        }

    }

    for(int i = 0; i < plannedColleges.size(); i++)
                {
                    qDebug() << plannedColleges[i];
                }

}

void tripPlanner::planAlgorithm(QString start, int dist)
{
    int distTo;
    plannedColleges<< start;
    QSqlQuery *query = new QSqlQuery;

    query->prepare("SELECT distance, endCollege FROM Distances WHERE startCollege = (:start) ORDER BY distance ASC");
    query->bindValue(":start", start);

    if(query->exec())
    {
        while(query->next())// goes to next college
        {

            QString temp = query->value("endCollege").toString();
            if(!planDoesExist(temp) && collegeDoesExist(temp))
            {
                dist+= query->value("distance").toInt();
                distTo = query->value("distance").toInt();
                distanceTo << distTo;
                qDebug() << "--------------------";
                qDebug() << distanceTo[0];
                qDebug() << distTo;
                distance = dist;
                start = query->value("endCollege").toString();
                planAlgorithm(start, dist); // recursive call

            }

        }
    }
    else
    {
        qDebug() << "failed";
    }

    qDebug() << distance;

}

bool tripPlanner::collegeDoesExist(QString colName)
{
    for(int i = 0; i < selectedColleges.size(); i++)
    {
        if(colName == selectedColleges[i])
        {
            return true;
        }
    }

    return false;
}

bool tripPlanner::planDoesExist(QString colName)
{
    for(int i = 0; i < plannedColleges.size(); i++)
    {
        if(colName == plannedColleges[i])
        {
            return true;
        }
    }

    return false;
}

void tripPlanner::showTrip(QString ID)
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << ID;

    qry->prepare("SELECT college FROM Trips WHERE tripID = (:tripId)");
    qry->bindValue(":tripId" , ID);
    if(qry->exec())
    {
        qDebug() << "trip table updated.";
    }
    else
        qDebug() << "failed trip table";

    model->setQuery(*qry);

    //clear here?
    ui->window->setModel(model);
    ui->window->resizeColumnsToContents();
}



void tripPlanner::onStartClick()
{

    if(!plannedColleges.isEmpty())
    {
       // this->ui->startLabel->setText("");
        this->hide();
        tripprogress *prog = new tripprogress(this);

        prog->tripID = id;

        qDebug() << prog->tripID;
        prog->show();
    }
    else
    {


        QMessageBox::information(this,"title","Create a trip first");
    }


}


void tripPlanner::prePlanned()
{
    selectedColleges.clear();
    QSqlQuery *query = new QSqlQuery();
    int i = 0;

    QString startingCollege;
    startingCollege = this->ui->colName->currentText();

    int stops;
    stops= ui->spinBox->value();

if(stops>12)
{
     QMessageBox::information(this,"title","must not be bigger than 10");

}
else
{
    query->prepare("SELECT DISTINCT startCollege FROM Distances");
    if(!query->exec())
    {
        qDebug() << "tripPlanner initializeList query failed";

       }

    else
    {
        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            checkBoxVector[i]->setCheckState(Qt::CheckState::Checked);

        }
        while(query->next())
        {

            if(checkBoxVector[i]->checkState() == Qt::CheckState::Checked)
           {
               QString temp = query->value("startCollege").toString();
               selectedColleges << temp;
               qDebug()<< temp << endl;

           }
           i++;
          }
    }


}

}


