#ifndef EDIT_UNIVERSITIES_H
#define EDIT_UNIVERSITIES_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class edit_universities;
}

class edit_universities : public QDialog
{
    Q_OBJECT

public:
    explicit edit_universities(QWidget *parent = nullptr);
    ~edit_universities();
    QSqlDatabase mydb;

private slots:


    void on_pushButton_edit_clicked();

    void on_displayButton_clicked();

private:
    Ui::edit_universities *ui;
};

#endif // EDIT_UNIVERSITIES_H
