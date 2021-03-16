#ifndef CONFIRMPAGE_H
#define CONFIRMPAGE_H

#include <QDialog>
#include "QDebug"
#include <QPixmap>



namespace Ui {
class confirmpage;
}

class confirmpage : public QDialog
{
    Q_OBJECT
public:

    explicit confirmpage(QWidget *parent = nullptr);


    ~confirmpage();

    confirmpage(QWidget *parent, bool &returnAnswer);

    bool getData();

private slots:

    void on_okButton_released();


    void on_cancelButton_released();
private:

    Ui::confirmpage *ui;


    bool answer = false;
};



#endif // CONFIRMPAGE_H
