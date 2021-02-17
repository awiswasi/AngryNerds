#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

#include <QDialog>

namespace Ui {
class admin_window;
}

class admin_window : public QDialog
{
    Q_OBJECT

public:
    explicit admin_window(QWidget *parent = nullptr);
    ~admin_window();

private:
    Ui::admin_window *ui;
};

#endif // ADMIN_WINDOW_H
