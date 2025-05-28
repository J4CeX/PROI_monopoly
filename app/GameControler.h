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
    
public slots:
    void saveSettings(const QString& bankMoney, const QString& playerName);
    void startNewGame();
    
signals:
    void settingsSaved(bool success);
    void validationError(const QString& message);
    void createdGame();
    
private:
    Game _game;
};