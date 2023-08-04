#include "RestReminder.h"
#include <QtWidgets/QApplication>


RestReminder::RestReminder(QApplication* a, QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    controller.setQApplication(a);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);  // 此行windows下需
}

RestReminder::~RestReminder() {}
