#include "RestReminder.h"
#include <QtWidgets/QApplication>


RestReminder::RestReminder(QApplication* a, QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    controller.setQApplication(a);
}

RestReminder::~RestReminder() {}
