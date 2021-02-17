#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <QDialog>
#include "admin_window.h"

namespace Ui {
class login_screen;
}

class login_screen : public QDialog
{
    Q_OBJECT

public:
    explicit login_screen(QWidget *parent = nullptr);
    ~login_screen();

private slots:
    void on_pushButton_Login_clicked();

private:
    Ui::login_screen *ui;
    admin_window *admin;
};

#endif // LOGIN_SCREEN_H
