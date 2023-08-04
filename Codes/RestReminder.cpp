#include "RestReminder.h"
#include <QtWidgets/QApplication>


RestReminder::RestReminder(int argc, char* argv[]) : QApplication(argc, argv) {
    controller.setQApplication(this);
    controller.startTimer();
    QApplication::setQuitOnLastWindowClosed(false);
}

RestReminder::~RestReminder() {}
