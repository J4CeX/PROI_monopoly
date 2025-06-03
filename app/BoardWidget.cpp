#include "BoardWidget.h"
BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent) {
    board.load(":/board/monopoly_board.png");
    setFixedSize(board.size());
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
        int pId = p.getPlayerId()-1;
        QPixmap pix = pixmapForToken(p.getToken());
        std::pair<int, int> startPos = this->coordinates[0];
        std::pair<int, int> pOffset = this->offset[pId];
        QPoint pos(startPos.first + pOffset.first, startPos.second + pOffset.second);
        pawns[pId] = {pos, pix};
    }
    update();
}

void BoardWidget::addHouse(int position, int houseLevel) {

    QPixmap housePixmap(":/board/house1.png");
    housePixmap = housePixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    std::pair<int, int> pos = coordinates[position];

    int houseCount = houses[position].size();
    QPoint basePos(pos.first, pos.second);
    std::pair<int, int> hOffset = this->offset[houseCount];
    QPoint qOffset(hOffset.first, hOffset.second); 

    House h = { basePos + qOffset, housePixmap };
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



void BoardWidget::updatePawnPosition(int playerId, int fieldId) {
    if (pawns.contains(playerId)) {
        std::pair<int, int> fieldPos = this->coordinates[fieldId];
        std::pair<int, int> pOffset = this->offset[playerId];
        pawns[playerId].position = QPoint(fieldPos.first + pOffset.first, fieldPos.second + pOffset.second);
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
