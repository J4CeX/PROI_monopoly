#pragma once
#include <QObject>
#include <QSettings>
#include <QString>
#include "Game.hpp"
#include "Player.hpp"
#include <iostream>
#include <memory>
#include <map>

using namespace Monopoly;

class GameController : public QObject
{
    Q_OBJECT
    
public:
    explicit GameController(QObject *parent = nullptr);
    QString getPlayerAmount() const;
    QStringList playerNamesList();
    QStringList playerOwnedFields(int idx) const;
    QStringList currentPlayerOwnedFields() const;
    QString currentPlayerName() const;
    Player getPlayer(int idx) const;
    QString currentPlayerBalance() const;
    QString currentPlayerPosition() const;
    QString currentPlayerField();
    QString currentPlayerToken() const;
    QString currentPlayerIndex() const;
    int getCurrentPlayerIndex() const;
    std::pair<int, int> fieldCoords(int idx) const;
    std::vector<Token> playerTokens() const;
    std::vector<Player> getPlayers() const { return this->_game.getPlayers(); };
    QString getGameTurn() const;
    
public slots:
    void saveSettings(const QString& bankMoney, const QString& playerName);
    void startNewGame();
    void addPlayer(const QString& playerName, const QString& tokenText);
    void tryStartGame();
    void rollDice();
    void findNextPlayer();
    void buyField();
    
signals:
    void settingsSaved(bool success);
    void validationError(const QString& message);
    void createdGame();
    void addedPlayer(const QString& msg);
    void failAddedPlayer(const QString& msg);
    void fail(const QString& msg);
    void startedGame();
    void rolledDice(const QString& results, const QString& field);
    void isBuyableField(bool isBuyable, int cost);
    void triedBuyField(int code, const QString& q_field);
    
private:
    Game _game;
    int _newestPlayerId = 0;
};