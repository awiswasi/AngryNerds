#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

#include <QDialog>
#include "edit_universities.h"

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

private:
    Ui::admin_window *ui;
    edit_universities *editUni;
};

#endif // ADMIN_WINDOW_H
