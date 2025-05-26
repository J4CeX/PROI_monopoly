#pragma once
#include <QObject>
#include <QSettings>
#include <QString>

class GameController : public QObject
{
    Q_OBJECT
    
public:
    explicit GameController(QObject *parent = nullptr);
    
public slots:
    void saveSettings(const QString& bankMoney, const QString& playerName);
    
signals:
    void settingsSaved(bool success);
    void validationError(const QString& message);
    
private:
    QSettings m_settings;
    int _bankMoney;
    int _playerMoney;
};