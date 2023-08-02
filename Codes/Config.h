#pragma once

#include <QFile>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

class Config {
public:
    bool isOk;
    int worktime{};
    int work_timeout{};
    int resttime{};
    int rest_timeout{};

    Config() : isOk(false) {
        // Read config from file
        QFile configFile("../Settings/conf.json");
        if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file.";
            return;
        }
        QByteArray data = configFile.readAll();
        configFile.close();

        // Parse config file
        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &error);
        if (jsonDocument.isNull()) {
            qDebug() << "Failed to parse JSON data: " << error.errorString();
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