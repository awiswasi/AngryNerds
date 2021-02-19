#ifndef EDIT_UNIVERSITIES_H
#define EDIT_UNIVERSITIES_H

#include <QDialog>

namespace Ui {
class edit_universities;
}

class edit_universities : public QDialog
{
    Q_OBJECT

public:
    explicit edit_universities(QWidget *parent = nullptr);
    ~edit_universities();

private:
    Ui::edit_universities *ui;
};

#endif // EDIT_UNIVERSITIES_H
