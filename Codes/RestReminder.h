#pragma once

#include "Controller.h"
#include <QtWidgets/QApplication>


class RestReminder : public QApplication {
    Q_OBJECT

public:
    RestReminder(int argc, char* argv[]);
    ~RestReminder();

private:
    Controller controller;
};
