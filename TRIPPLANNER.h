#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QDialog>
#include <QList>




namespace Ui {
class tripPlanner;
}

class tripPlanner : public QDialog
{
    Q_OBJECT

public:
    /*

    Constructor sets up ui for tripPlanner
    and executes initalizeList(), and updateCombo()
    for QDialog
    */
    explicit tripPlanner(QWidget *parent = nullptr);

    /*
     brief Destructor

    Close the tripPlanner UI
    */
    ~tripPlanner();

    /**
    brief initalizes list of colleges and their distances from start colleges, as well as the UI for selecting and pushing colleges via checkBoxVector
     return nothing - void
    */
    void initializeList();

    /**
     brief stores and displays list of user/student selected colleges for current trip in progress/planned
     return nothing - void
    */
    void selectedCollegeList();

    /*
    brief method that calculates most efficient route between all selected colleges, from start to finish
    return nothing - void
    start - starting destination
    dist - stores distance between destination for recursive
    */
    void planAlgorithm(QString start, int dist);

    /*
    brief method that checks whether college in sql col exists
    return bool - true or false(whether data exists)
    colname - college col to be checked
    */
    bool collegeDoesExist(QString colName);

    /*
    brief method that checks whether plan in sql col exists
    return bool - true or false(whether data exists)
     colname - plan col to be checked
    */
    bool planDoesExist(QString colName);

    /*
    brief updates sql table with college data, with trip starting and ending colleges with their distances
     start, starting college for trip
     return none- void
    */
    void updateCollegeTable(QString start);

    /*
     brief updates sql table with souvenir data, with prices, quantity, souvenier name, and associated college
     start, starting college for trip
     return none- void
    */
    void updateSouvTable(QString start);

    /*
    brief updates sql table with tripID data and displays/updates trip data table
     ID - tripID
     return none- void
    */
    void showTrip(QString ID);

    void updateCombo();


private slots:

    // brief manages and updates checkbox for user selected colleges
    // return none- void

    void ChecboxChanged();




private:

    // brief points to tripPlanner UI

    Ui::tripPlanner *ui;


    // brief vector for managing user selecting colleges via checkbox

    QVector<QCheckBox*> checkBoxVector;


    // brief  a string to hold the selected colleges - should be helpful for the plan trip algorithm

    QStringList selectedColleges; // a string to hold the selected colleges - should be helpful for the plan trip algorithm


    // brief  a string to hold the planned colleges - should be helpful for the plan trip algorithm

    QStringList plannedColleges;


     // brief field member holding distance

    int distance;


    //brief field member holding tripID

    QString id;

    QList<int> distanceTo;




};

#endif // TRIPPLANNER_H
