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
	QMenu* restMenu;
	QMenu* workMenu;
	QMenu* exitMenu;

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
	}

	void stopWork() {
		setStatus(worktime_timeout);
	}

	void startRest() {
		setStatus(resttime);
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
		restMenu = new QMenu();
		QAction* restAction = new QAction("Rest", restMenu);
		restMenu->addAction(restAction);
		trayIcon->setContextMenu(restMenu);
		QObject::connect(restAction, &QAction::triggered, [&]() {
			startRest();
	    });

		workMenu = new QMenu();
		QAction* workAction = new QAction("Work", workMenu);
		workMenu->addAction(workAction);
		QObject::connect(workAction, &QAction::triggered, [&]() {
			startWork();
		});

		exitMenu = new QMenu();
		QAction* exitAction = new QAction("Exit", exitMenu);
		exitMenu->addAction(exitAction);
		trayIcon->setContextMenu(exitMenu);
		QObject::connect(exitAction, &QAction::trigger, [&]() {
			a->exit();
		});
	}

	void setQApplication(QApplication* a) {
		this->a = a;
	}
};
// QMessageBox::information(nullptr, "Information", "menu is clicked!");