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
    work_timeout = 2,
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
    QMessageBox* workMsgbox;
    QMessageBox* restMsgbox;

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
        qDebug() << "Start to work";
        setStatus(worktime);
        menu->removeAction(workAction);
        menu->removeAction(exitAction);
        menu->addAction(restAction);
        menu->addAction(exitAction);
        workMsgbox->hide();
    }

    void stopWork() {
        setStatus(work_timeout);
    }

    void startRest() {
        qDebug() << "Start to rest";
        setStatus(resttime);
        menu->removeAction(restAction);
        menu->removeAction(exitAction);
        menu->addAction(workAction);
        menu->addAction(exitAction);
        restMsgbox->hide();
    }

    void stopRest() {
        setStatus(rest_timeout);
    }

    void alert(QMessageBox* msgbox) {
        msgbox->setWindowFlags(workMsgbox->windowFlags() | Qt::WindowStaysOnTopHint);
        msgbox->show();
        QTimer::singleShot(500, [msgbox]() {  // 弹出时置顶是为了即使电脑处于全屏状态，也要能够被看到。弹出后0.5秒就可以取消置顶了
            msgbox->setWindowFlags(msgbox->windowFlags() & ~Qt::WindowStaysOnTopHint);
            msgbox->show();  // 还需再show一次
        });
    }

    void refreshIconAndStatus() {
        // Status
        secCnt++;
        if (status == worktime && secCnt == config.worktime) {  // 工作时间达标，休息提醒
            qDebug() << "Please rest";
            status = work_timeout;
            secCnt = 0;
            trayIcon->showMessage("Information", "Please rest", QSystemTrayIcon::Information, 5000);
        }
        else if (status == work_timeout && secCnt == config.work_timeout) {  // 工作时间超出work_timeout还未休息
            qDebug() << "You must rest!";
            alert(restMsgbox);
        }
        else if (status == resttime && secCnt == config.resttime) {  // 休息时间达标，工作提醒
            qDebug() << "Comeback to work";
            status = rest_timeout;
            secCnt = 0;
            trayIcon->showMessage("Information", "Please work", QSystemTrayIcon::Information, 5000);
        }
        else if (status == rest_timeout && secCnt == config.rest_timeout) {  // 休息时间超出rest_timeout还未工作
            qDebug() << "You must work!";
            alert(workMsgbox);
        }

        // Icon
        QPixmap pixmap = trayIcon->icon().pixmap(16, 16);
        QPainter painter(&pixmap);
        
        if (status == worktime) {

        }
        else if (status == work_timeout) {
            QColor color(255, 0, 0);
            painter.fillRect(0, 0, 16, 16, color);
        }
        else if (status == resttime) {

        }
        else {  // rest_timeout
            QColor color(0, 255, 0);
            painter.fillRect(0, 0, 16, 16, color);
        }

        trayIcon->setIcon(pixmap);
    }

public:
    Controller() {
        trayIcon = new QSystemTrayIcon();
        trayIcon->setIcon(QPixmap(16, 16));
        trayIcon->show();
        trayIcon->showMessage("Information", "It's running at the system tray area", QSystemTrayIcon::Information, 5000);

        workMsgbox = new QMessageBox(QMessageBox::Warning, "Warn", "You must work! MUST!", QMessageBox::Ok);
        restMsgbox = new QMessageBox(QMessageBox::Warning, "Warn", "You must rest! MUST!", QMessageBox::Ok);

        // 右键菜单
        menu = new QMenu();
        trayIcon->setContextMenu(menu);

        restAction = new QAction("Rest", menu);
        menu->addAction(restAction);
        QObject::connect(restAction, &QAction::triggered, [&]() {
            qDebug() << "Rest menu clicked!";
            startRest();
        });

        workAction = new QAction("Work", menu);
        QObject::connect(workAction, &QAction::triggered, [&]() {
            qDebug() << "Work menu clicked!";
            startWork();
        });

        exitAction = new QAction("Exit", menu);
        menu->addAction(exitAction);
        QObject::connect(exitAction, &QAction::triggered, [&]() {
            qDebug() << "Exit menu clicked!";
            a->exit();
        });
    }

    void setQApplication(QApplication* a) {
        this->a = a;
    }

    void startTimer() {
        QTimer* timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [&]() {
            refreshIconAndStatus();
        });
        timer->start(1000);
    }
};