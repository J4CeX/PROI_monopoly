#pragma once
#include <QWidget>
#include <QPainter>
#include "Game.hpp"
#include "GameController.h"
class BoardWidget : public QWidget {
    Q_OBJECT

public:
    BoardWidget(int size, QWidget *parent = nullptr);

    void setPlayers(const std::vector<Player>& players);
    void updatePawnPosition(int playerId, int fieldId);
    void addHouse(int position, int houseLevel);
    void removeHouse(int position);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap board;
    struct Pawn {
        QPoint position;
        QPixmap pixmap;
    };
    struct House {
        QPoint position;
        QPixmap pixmap;
    };
    QMap<int, QVector<House>> houses;
    QMap<int, Pawn> pawns;
    QPixmap pixmapForToken(Token token);
    QPoint absoluteCoordinates(int index) const;
    std::vector<QPointF> relativeCoordinates = {
        {0.928, 0.928}, {0.839, 0.928}, {0.75, 0.928}, {0.661, 0.928}, {0.561, 0.928},
        {0.472, 0.928}, {0.383, 0.928}, {0.294, 0.928}, {0.206, 0.928}, {0.117, 0.928},
        {0.028, 0.928}, {0.028, 0.839}, {0.028, 0.75}, {0.028, 0.656}, {0.028, 0.567},
        {0.028, 0.478}, {0.028, 0.389}, {0.028, 0.289}, {0.028, 0.2},  {0.028, 0.111},
        {0.028, 0.022}, {0.117, 0.022}, {0.206, 0.022}, {0.294, 0.022}, {0.383, 0.022},
        {0.472, 0.022}, {0.561, 0.022}, {0.656, 0.022}, {0.744, 0.022}, {0.839, 0.022},
        {0.928, 0.022}, {0.928, 0.111}, {0.928, 0.2},   {0.928, 0.289}, {0.928, 0.383},
        {0.928, 0.472}, {0.928, 0.561}, {0.928, 0.656}, {0.928, 0.744}, {0.928, 0.833}
    };

    std::vector<QPointF> relativeOffsets = {
        {-0.022, -0.0189}, {0.0156, -0.0189}, {0.0156, 0.0189}, {-0.022, 0.0189}, {-0.0033, 0.0}
    };


};
