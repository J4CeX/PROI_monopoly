#include <iostream>
#include <QObject>
#include <QString>
#include <map>
#include "GameControler.h"
#include "Game.hpp"
#include "Player.hpp"

using namespace Monopoly;
using namespace MonopolyPlayer;

GameController::GameController(QObject *parent): QObject(parent) { }

void GameController::saveSettings(const QString& bankMoneyStr, const QString& playerMoneyStr)
{
    bool ok;
    int bankMoney = bankMoneyStr.toInt(&ok);
    if(!ok || bankMoney <= 0) {
        emit validationError("Incorrect initial bank money value");
        return;
    }
    int playerMoney = playerMoneyStr.toInt(&ok);
    if(!ok || bankMoney <= 0) {
        emit validationError("Incorrect initial player money value");
        return;
    }
    emit settingsSaved(true);
}

void GameController::startNewGame()
{
    Game new_game;
    this->_game = new_game;
    this->_newestPlayerId = 0;
}

void GameController::addPlayer(const QString& playerName, const QString& tokenText)
{
    if(this->_game.getPlayers().size() >= 4)
    {
        emit failAddedPlayer("Max player amount is 4");
        return;
    }
    std::string p_name_std = playerName.toUtf8().constData();
    std::string p_token_std = tokenText.toUtf8().constData();
    if(p_name_std.empty())
    {
        emit failAddedPlayer("Player name cannot be empty!");
        return;
    }
    std::map<std::string, Token> token_map{{"Race Car", Token::raceCar},
                                            {"Top Hat", Token::topHat},
                                            {"Thimble", Token::thimble},
                                            {"Scottish Terrier", Token::scottishTerrier},
                                            {"Sack of Money", Token::sackOfMoney},
                                            {"Cat", Token::cat},
                                            {"Penguin", Token::penguin},
                                            {"Rubber Duck", Token::rubberDuck}};
    try
    {
        Token p_token = token_map[p_name_std];
        Player new_player(this->_newestPlayerId, p_name_std, p_token);
        this->_newestPlayerId++;
        this->_game.addPlayer(new_player);
        std::string msg_std = "Player " + p_name_std + " (" +p_token_std + ") added!";
        QString msg = QString::fromStdString(msg_std); 
        emit addedPlayer(msg);
    }
    catch(const std::exception& e)
    {
        emit failAddedPlayer(e.what());
    }
}

QString GameController::getPlayerAmount() const
{
    int players = this->_game.getPlayers().size();
    QString q_id = QString::number(players);
    return q_id;
}

QStringList GameController::playerNamesList()
{
    QStringList player_names;
    for(Player player : this->_game.getPlayers())
    {
        player_names.append(QString::fromStdString(player.getName()));
    }
    return player_names;
}