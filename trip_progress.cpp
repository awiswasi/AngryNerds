#include "trip_progress.h"
#include "ui_trip_progress.h"

trip_progress::trip_progress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trip_progress)
{
    ui->setupUi(this);
}

trip_progress::~trip_progress()
{
    delete ui;
}
