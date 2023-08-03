#include "RestReminder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RestReminder w(&a);
    w.show();
    return a.exec();
}
