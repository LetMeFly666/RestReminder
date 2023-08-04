#include "RestReminder.h"
#include <QtWidgets/QApplication>


RestReminder::RestReminder(int argc, char* argv[]) : QApplication(argc, argv) {
    controller.setQApplication(this);
    controller.startTimer();
}

RestReminder::~RestReminder() {}
