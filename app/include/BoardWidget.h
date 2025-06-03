#pragma once
#include <QWidget>
#include <QPainter>
#include "Game.hpp"
#include "GameController.h"
class BoardWidget : public QWidget {
    Q_OBJECT

public:
    BoardWidget(QWidget *parent = nullptr);

    void setPlayers(const std::vector<Player>& players);
    void updatePawnPosition(int playerId, int fieldId);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap board;
    struct Pawn {
        QPoint position;
        QPixmap pixmap;
    };
    QMap<int, Pawn> pawns;
    QPixmap pixmapForToken(Token token);
    std::pair<int, int> coordinates[40] = {{835, 835}, {755, 835}, {675, 835}, {595, 835}, {505, 835}, {425, 835}, {345, 835}, {265, 835}, {185, 835},
                                       {105, 835}, {25, 835}, {25, 755}, {25, 675}, {25, 590}, {25, 510}, {25, 430}, {25, 350}, {25, 260},
                                       {25, 180}, {25, 100}, {25, 20}, {105, 20}, {185, 20}, {265, 20}, {345, 20}, {425, 20}, {505, 20},
                                       {590, 20}, {670, 20}, {755, 20}, {835, 20}, {835, 100}, {835, 180}, {835, 260}, {835, 345}, {835, 425},
                                       {835, 505}, {835, 590}, {835, 670}, {835, 750}};
    std::pair<int, int> offset[4] = {{-17, -17}, {17, -17}, {17, 17}, {-17, 17}};
};
