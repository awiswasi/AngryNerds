#ifndef EDIT_SOUVENIRS_H
#define EDIT_SOUVENIRS_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class edit_souvenirs;
}

class edit_souvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit edit_souvenirs(QWidget *parent = nullptr);
    ~edit_souvenirs();
    QSqlDatabase souvdb;

private slots:
    void on_pushButton_3_clicked();

    void on_displaySouvenirsButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_searchSouvenirButton_clicked();

private:
    Ui::edit_souvenirs *ui;
};

#endif // EDIT_SOUVENIRS_H
