#include "BoardWidget.h"
BoardWidget::BoardWidget(int size, QWidget *parent) : QWidget(parent) {
    board.load(":/board/board_thick_logo.png");
    board = board.scaled(size, size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setFixedSize(size, size);
}

QPixmap BoardWidget::pixmapForToken(Token token) {
    switch (token) {
        case Token::raceCar:
            return QPixmap(":/board/racecar.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::topHat:
            return QPixmap(":/board/tophat.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::thimble:
            return QPixmap(":/board/thimble.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::scottishTerrier:
            return QPixmap(":/board/scottishterrier.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::sackOfMoney:
            return QPixmap(":/board/sackofmoney.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::cat:
            return QPixmap(":/board/cat.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::penguin:
            return QPixmap(":/board/penguin.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::rubberDuck:
            return QPixmap(":/board/rubberduck.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        default:
            return QPixmap();
    }
}

void BoardWidget::setPlayers(const std::vector<Player>& players) {
    pawns.clear();
    for (const Player& p : players) {
        int pId = p.getPlayerId() - 1;
        QPixmap pix = pixmapForToken(p.getToken());

        QPointF relPos = relativeCoordinates[0];
        QPoint basePos(
            static_cast<int>(relPos.x() * board.width()),
            static_cast<int>(relPos.y() * board.height())
        );

        QPointF relOffset = relativeOffsets[pId];
        QPoint offset(
            static_cast<int>(relOffset.x() * board.width()),
            static_cast<int>(relOffset.y() * board.height())
        );

        pawns[pId] = {basePos + offset, pix};
    }
    update();
}


void BoardWidget::addHouse(int position, int houseLevel) {
    QPixmap housePixmap(":/board/house1.png");
    housePixmap = housePixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPointF relPos = relativeCoordinates[position];
    QPoint basePos(
        static_cast<int>(relPos.x() * board.width()),
        static_cast<int>(relPos.y() * board.height())
    );

    int houseCount = houses[position].size();
    if (houseCount >= relativeOffsets.size()) return; 

    QPointF relOffset = relativeOffsets[houseCount];
    QPoint offset(
        static_cast<int>(relOffset.x() * board.width()),
        static_cast<int>(relOffset.y() * board.height())
    );

    House h = { basePos + offset, housePixmap };
    houses[position].append(h);

    update();
}


void BoardWidget::removeHouse(int position) {
    if (!houses.contains(position)) return;

    auto& houseList = houses[position];
    if (!houseList.isEmpty()) {
        houseList.removeLast();
        if (houseList.isEmpty()) {
            houses.remove(position);
        }
        update();
    }
}

QPoint BoardWidget::absoluteCoordinates(int index) const {
    QPointF rel = relativeCoordinates[index];
    return QPoint(rel.x() * board.width(), rel.y() * board.height());
}


void BoardWidget::updatePawnPosition(int playerId, int fieldId) {
    if (pawns.contains(playerId)) {
        QPoint base = absoluteCoordinates(fieldId);
        QPointF offsetRel = relativeOffsets[playerId];
        QPoint offset(offsetRel.x() * board.width(), offsetRel.y() * board.height());
        pawns[playerId].position = base + offset;
        update();
    }
}

void BoardWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, board);
    for (const QVector<House>& houseList : houses.values()) {
        for (const House& h : houseList) {
            painter.drawPixmap(h.position, h.pixmap);
        }
}
    for (const Pawn& p : pawns.values()) {
        painter.drawPixmap(p.position, p.pixmap);
    }
}
