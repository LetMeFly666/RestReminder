#pragma once

#include <QFile>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QMessageBox>

class Config {
public:
    bool isOk;
    int worktime = 1800;
    int work_timeout = 1800;
    int resttime = 300;
    int rest_timeout = 600;

    Config() : isOk(false) {
        // Read config from file
        QFile configFile("../Settings/conf.json");
        if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file.";
            QMessageBox::warning(nullptr, "Warn", "Failed to open config file.<br>See restreminder.tisfy.eu.org for more");
            return;
        }
        QByteArray data = configFile.readAll();
        configFile.close();

        // Parse config file
        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &error);
        if (jsonDocument.isNull()) {
            qDebug() << "Failed to parse JSON data: " << error.errorString();
            QMessageBox::warning(nullptr, "Warn", "Failed to parse JSON data:<br>" + error.errorString() + "<br>See restreminder.tisfy.eu.org for more");
            return;
        }
        QJsonObject config = jsonDocument.object();
        worktime = config["worktime"].toInt();
        work_timeout = config["work_timeout"].toInt();
        resttime = config["resttime"].toInt();
        rest_timeout = config["rest_timeout"].toInt();
        qDebug() << "worktime: " << worktime;
        qDebug() << "work_timeout: " << work_timeout;
        qDebug() << "resttime: " << resttime;
        qDebug() << "rest_timeout: " << rest_timeout;

        isOk = true;
    }
};