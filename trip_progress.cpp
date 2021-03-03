#ifndef TRIP_PROGRESS_H
#define TRIP_PROGRESS_H

#include <QDialog>

namespace Ui {
class trip_progress;
}

class trip_progress : public QDialog
{
    Q_OBJECT

public:
    explicit trip_progress(QWidget *parent = nullptr);
    ~trip_progress();

private:
    Ui::trip_progress *ui;
};

#endif // TRIP_PROGRESS_H
