#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

#include <QDialog>
#include "edit_universities.h"
#include "edit_souvenirs.h"

namespace Ui {
class admin_window;
}

class admin_window : public QDialog
{
    Q_OBJECT

public:
    explicit admin_window(QWidget *parent = nullptr);
    ~admin_window();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::admin_window *ui;
    edit_universities *editUni;
    edit_souvenirs *editSouv;
};

#endif // ADMIN_WINDOW_H
