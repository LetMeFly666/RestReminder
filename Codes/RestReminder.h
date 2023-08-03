#pragma once

#include "ui_RestReminder.h"
#include "Controller.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>


class RestReminder : public QMainWindow {
    Q_OBJECT

public:
    RestReminder(QApplication* a, QWidget *parent = nullptr);
    ~RestReminder();

private:
    Ui::RestReminderClass ui;
    Controller controller;
};
