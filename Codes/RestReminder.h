#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RestReminder.h"

class RestReminder : public QMainWindow
{
    Q_OBJECT

public:
    RestReminder(QWidget *parent = nullptr);
    ~RestReminder();

private:
    Ui::RestReminderClass ui;
};