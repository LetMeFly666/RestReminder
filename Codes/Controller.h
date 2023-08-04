#pragma once
#include "Config.h"
#include <QtWidgets/QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QPainter>
#include <QAction>
#include <QTimer>
#include <QMenu>

enum Status {
    worktime = 1,
    worktime_timeout = 2,
    resttime = 3,
    rest_timeout = 4
};

class Controller {
private:
    QApplication* a = nullptr;
    Status status = worktime;
    int secCnt = 0;
    Config config;
    QSystemTrayIcon* trayIcon;
    QMenu* menu;
    QAction* workAction;
    QAction* restAction;
    QAction* exitAction;

    int getStatus() {
        return status;
    }

    int getCntTime() {
        return secCnt;
    }

    void setStatus(Status status) {
        this->status = status;
        secCnt = 0;
    }

    void startWork() {
        setStatus(worktime);
        menu->removeAction(restAction);
        menu->removeAction(exitAction);
        menu->addAction(workAction);
        menu->addAction(exitAction);
    }

    void stopWork() {
        setStatus(worktime_timeout);
    }

    void startRest() {
        setStatus(resttime);
        menu->removeAction(workAction);
        menu->removeAction(exitAction);
        menu->addAction(restAction);
        menu->addAction(exitAction);
    }

    void stopRest() {
        setStatus(rest_timeout);
    }

    void refreshIcon() {
        QPixmap pixmap = trayIcon->icon().pixmap(16, 16);
        QPainter painter(&pixmap);
        QColor color(qrand() % 255, qrand() % 255, qrand() % 255);
        painter.fillRect(0, 0, 16, 16, color);
        trayIcon->setIcon(pixmap);
    }

public:
    Controller() {
        trayIcon = new QSystemTrayIcon();
        trayIcon->setIcon(QPixmap(16, 16));
        trayIcon->show();

        // ¶¨Ê±Æ÷
        QTimer* timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [&]() {
            refreshIcon();
        });
        timer->start(1000);

        // ÓÒ¼ü²Ëµ¥
        menu = new QMenu();
        restAction = new QAction("Rest", menu);
        menu->addAction(restAction);
        trayIcon->setContextMenu(menu);
        QObject::connect(restAction, &QAction::triggered, [&]() {
            startRest();
        });

        workAction = new QAction("Work", menu);
        QObject::connect(workAction, &QAction::triggered, [&]() {
            startWork();
        });

        exitAction = new QAction("Exit", menu);
        menu->addAction(exitAction);
        trayIcon->setContextMenu(menu);
        QObject::connect(exitAction, &QAction::trigger, [&]() {
            a->exit();
        });
    }

    void setQApplication(QApplication* a) {
        this->a = a;
    }
};
// QMessageBox::information(nullptr, "Information", "menu is clicked!");