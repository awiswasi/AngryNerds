#ifndef DISPLAY_COLLEGES_H
#define DISPLAY_COLLEGES_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class display_colleges;
}

class display_colleges : public QDialog
{
    Q_OBJECT

public:
    explicit display_colleges(QWidget *parent = nullptr);
    ~display_colleges();
    QSqlDatabase mydb;


private slots:
    void on_pushButton_clicked();

private:
    Ui::display_colleges *ui;
};

#endif // DISPLAY_COLLEGES_H
