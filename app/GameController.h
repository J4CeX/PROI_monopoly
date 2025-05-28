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
    QString currentPlayerName() const;
    Player getPlayer(int idx) const;
    QString currentPlayerBalance() const;
    QString currentPlayerPosition() const;
    QString currentPlayerToken() const;
    QString currentPlayerIndex() const;
    std::pair<int, int> fieldCoords(int idx) const;
    
public slots:
    void saveSettings(const QString& bankMoney, const QString& playerName);
    void startNewGame();
    void addPlayer(const QString& playerName, const QString& tokenText);
    void tryStartGame();
    
signals:
    void settingsSaved(bool success);
    void validationError(const QString& message);
    void createdGame();
    void addedPlayer(const QString& msg);
    void failAddedPlayer(const QString& msg);
    void fail(const QString& msg);
    void startedGame();
    
private:
    Game _game;
    int _newestPlayerId = 0;
};