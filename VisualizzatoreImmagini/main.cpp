#include "finestraimmagine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FinestraImmagine w;
    w.show();

    return a.exec();
}
