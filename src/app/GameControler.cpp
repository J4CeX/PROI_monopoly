#include <QObject>
#include <QSettings>
#include <QString>
#include "GameControler.h"

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
    _bankMoney = bankMoney;
    _playerMoney = playerMoney;
    emit settingsSaved(true);
}
