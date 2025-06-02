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
    std::pair<int, int> coordinates[40] = {{835, 835}, {585, 550}, {520, 550}, {460, 550}, {410, 550}, {370, 550}, {325, 550}, {275, 550}, {225, 550},
                                       {175, 550}, {115, 550}, {115, 500}, {115, 445}, {115, 390}, {115, 335}, {115, 285}, {115, 235}, {115, 175},
                                       {115, 110}, {115, 60}, {115, 10}, {175, 10}, {235, 10}, {295, 10}, {350, 10}, {410, 10}, {465, 10},
                                       {515, 10}, {560, 10}, {595, 10}, {645, 10}, {645, 70}, {645, 140}, {645, 210}, {645, 260}, {645, 320},
                                       {645, 365}, {645, 410}, {645, 460}, {645, 510}};
    std::pair<int, int> offset[4] = {{-17, -17}, {17, -17}, {17, 17}, {-17, 17}};
};
