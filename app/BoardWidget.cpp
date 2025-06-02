#include "BoardWidget.h"
// BoardWidget.cpp
BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent) {
    board.load(":/board/monopoly_board.png");
    setFixedSize(board.size()); // lub scaled rozmiar
}

QPixmap BoardWidget::pixmapForToken(Token token) {
    switch (token) {
        case Token::raceCar:
            return QPixmap(":/board/racecar_new.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::topHat:
            return QPixmap(":/board/tophat_new.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::thimble:
            return QPixmap(":/board/thimble_new.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        case Token::scottishTerrier:
            return QPixmap(":/board/scottishterrier_new.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        default:
            return QPixmap(); // pusty pixmap na wypadek błędu
    }
}

void BoardWidget::setPlayers(const std::vector<Player>& players) {
    pawns.clear();
    for (const Player& p : players) {
        int pId = p.getPlayerId()-1;
        QPixmap pix = pixmapForToken(p.getToken()); // załaduj na podstawie p.getToken()
        std::pair<int, int> startPos = this->coordinates[0];
        std::pair<int, int> pOffset = this->offset[pId];
        QPoint pos(startPos.first + pOffset.first, startPos.second + pOffset.second);  // wylicz pozycję
        pawns[pId] = {pos, pix};
    }
    update();
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
    for (const Pawn& p : pawns.values()) {
        painter.drawPixmap(p.position, p.pixmap);
    }
}
