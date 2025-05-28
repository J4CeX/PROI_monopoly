#pragma once
#include <QObject>
#include <QSettings>
#include <QString>
#include "Game.hpp"

using namespace Monopoly;

class GameController : public QObject
{
    Q_OBJECT
    
public:
    explicit GameController(QObject *parent = nullptr);
    QString getPlayerAmount() const;
    QStringList playerNamesList();
    
public slots:
    void saveSettings(const QString& bankMoney, const QString& playerName);
    void startNewGame();
    void addPlayer(const QString& playerName, const QString& tokenText);
    
signals:
    void settingsSaved(bool success);
    void validationError(const QString& message);
    void createdGame();
    void addedPlayer(const QString& msg);
    void failAddedPlayer(const QString& msg);
    
private:
    Game _game;
    int _newestPlayerId = 0;
};