#include "college_tour.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CollegeTour w;
    w.show();


    return a.exec();
}
