#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include <QDialog>
#include "addsouvenir.h"


namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:

    explicit AdminWindow(QWidget *parent = nullptr);


    void updateCollegeTable();


    void updateSouvenirTable();


    ~AdminWindow();

private slots:


    void on_addSouvenir_released();

    void on_removeSouvenir_released();

    void on_souvenirView_clicked(const QModelIndex &index);

    void on_pushButton_5_released();

    void on_add_clicked();

    void on_init_released();

    void on_clear_released();

    void on_update_clicked();

private:

    QString souve;

    Ui::AdminWindow *ui;

    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");

};

#endif // ADMINWINDOW_H
