#ifndef ADDSOUVENIR_H
#define ADDSOUVENIR_H

#include <QDialog>

namespace Ui {
class addSouvenir;
}

class addSouvenir : public QDialog
{
    Q_OBJECT

public:
    /*
     explicit default Constructor
    
     Constructor intializes UI for addSouvenir
     calls updateCombo()
     parent - for QDialog
    */
    explicit addSouvenir(QWidget *parent = nullptr);

    /*
    
     Close the addSouvenir UI
    */
    ~addSouvenir();

    /*
     Destructor
    
     updates sql query for startcollege and sets ui Model
    */
    void updateCombo();

private slots:
    void on_pushButton_2_released();

    /*
    executes process for adding a souvenir to database
    
    
    */
    void on_pushButton_released();


private:
    /*
    points to addSouvenir UI
    */
    Ui::addSouvenir *ui;



};
