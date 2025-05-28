#include <iostream>
#include <QObject>
#include <QSettings>
#include <QString>
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
}