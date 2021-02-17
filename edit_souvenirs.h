#ifndef EDIT_SOUVENIRS_H
#define EDIT_SOUVENIRS_H

#include <QDialog>

namespace Ui {
class edit_souvenirs;
}

class edit_souvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit edit_souvenirs(QWidget *parent = nullptr);
    ~edit_souvenirs();

private:
    Ui::edit_souvenirs *ui;
};

#endif // EDIT_SOUVENIRS_H
