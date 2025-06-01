#include "GameController.h"

std::map<std::string, Token> token_map{{"Race Car", Token::raceCar},
                                            {"Top Hat", Token::topHat},
                                            {"Thimble", Token::thimble},
                                            {"Scottish Terrier", Token::scottishTerrier},
                                            {"Sack of Money", Token::sackOfMoney},
                                            {"Cat", Token::cat},
                                            {"Penguin", Token::penguin},
                                            {"Rubber Duck", Token::rubberDuck}};

std::map<Token, std::string> str_token_map{{Token::raceCar, "Race Car"},
                                            {Token::topHat, "Top Hat"},
                                            {Token::thimble, "Thimble"},
                                            {Token::scottishTerrier, "Scottish Terrier"},
                                            {Token::sackOfMoney, "Sack of Money"},
                                            {Token::cat, "Cat"},
                                            {Token::penguin, "Penguin"},
                                            {Token::rubberDuck, "Rubber Duck"}};

std::pair<int, int> coordinates[40] = {{650, 550}, {585, 550}, {520, 550}, {460, 550}, {410, 550}, {370, 550}, {325, 550}, {275, 550}, {225, 550},
                                       {175, 550}, {115, 550}, {115, 500}, {115, 445}, {115, 390}, {115, 335}, {115, 285}, {115, 235}, {115, 175},
                                       {115, 110}, {115, 60}, {115, 10}, {175, 10}, {235, 10}, {295, 10}, {350, 10}, {410, 10}, {465, 10},
                                       {515, 10}, {560, 10}, {595, 10}, {645, 10}, {645, 70}, {645, 140}, {645, 210}, {645, 260}, {645, 320},
                                       {645, 365}, {645, 410}, {645, 460}, {645, 510}};

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
    this->_game = Game();
    this->_newestPlayerId = 0;
}

void GameController::tryStartGame()
{
    int players = this->_game.getPlayers().size();
    if(players < 2)
    {
        emit fail("At least 2 players needed to start the game!");
        return;
    }
    emit startedGame();
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
    try
    {
        Token p_token = token_map[p_token_std];
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

void GameController::rollDice()
{
    this->_game.rollDice();
    int r1 = _game.getDice().first, r2 = _game.getDice().second;
    std::string results = std::to_string(r1) + " " + std::to_string(r2); 
    QString q_results = QString::fromStdString(results);
    QString q_field = this->currentPlayerField();
    
    emit rolledDice(q_results, q_field);
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
        std::string p_info = player.getName() + " (" + str_token_map[player.getToken()] + ")";
        player_names.append(QString::fromStdString(p_info));
    }
    return player_names;
}

QString GameController::currentPlayerName() const
{
    int current_player_idx = this->_game.getCurrentPlayer();
    Player current_player = this->getPlayer(current_player_idx);
    std::string player_name = current_player.getName();
    QString q_player_name = QString::fromStdString(player_name);
    return q_player_name;
}

Player GameController::getPlayer(int idx) const
{
    return this->_game.getPlayers()[idx];
    
}

QString GameController::currentPlayerBalance() const
{
    int current_player_idx = this->_game.getCurrentPlayer();
    Player current_player = this->getPlayer(current_player_idx);
    int player_balance = current_player.getBalance();
    QString q_player_balance = QString::number(player_balance);
    return q_player_balance;
    
}

QString GameController::currentPlayerPosition() const
{
    int current_player_idx = this->_game.getCurrentPlayer();
    Player current_player = this->getPlayer(current_player_idx);
    int player_pos = current_player.getPosition();
    QString q_player_pos = QString::number(player_pos);
    return q_player_pos;
}

QStringList GameController::playerOwnedFields(int idx) const
{
    QStringList q_owned_fields;
    Player player = this->getPlayer(idx);
    const auto& fields = this->_game.getFields();
    int i = 0;
    for(const auto& field : fields)
    {
        TYPE type = field->getInfo();
        if(type == TYPE::STREET || type == TYPE::STATION || type == TYPE::UTILITY)
        {
            QString q_field = "boink";
            if (OwnableField* ownableField = dynamic_cast<OwnableField*>(field.get()))
            {
                size_t fieldOwner = ownableField->getOwner();
                if (ownableField->isOwned() && fieldOwner == idx)
                {
                    q_field = QString::fromStdString(ownableField->getName()) + "(" + QString::number(ownableField->getPosition()) + ")";
                    q_owned_fields.append(q_field);
                    i++;
                }
            }
        }
    }
    return q_owned_fields;
}

QString GameController::getGameTurn() const
{
    int turn = this->_game.getTurnCounter() + 1;
    QString q_turn = QString::number(turn);
    return q_turn;
}

QStringList GameController::currentPlayerOwnedFields() const
{
    int idx = this->_game.getCurrentPlayer();
    return this->playerOwnedFields(idx);
}

QString GameController::currentPlayerField()
{
    int idx = this->_game.getCurrentPlayer();
    Player current_player = this->getPlayer(idx);
    const auto& fields = this->_game.getFields();
    const auto& current_field = *(fields[current_player.getPosition()]);
    TYPE current_type = current_field.getInfo();
    
    QString q_field = "";
    if(current_type == TYPE::STREET || current_type == TYPE::STATION || current_type == TYPE::UTILITY)
    {
        if(const OwnableField* ownablefield = dynamic_cast<const OwnableField*>(&current_field))
        {
            q_field = QString::fromStdString(ownablefield->getName());
            int cost = ownablefield->getPurchasePrice();
            if(!ownablefield->isOwned()) emit isBuyableField(true, cost);
            else emit isBuyableField(false, cost);
        }
    }
    else if(current_type == TYPE::CHANCEFIELD)
    {
        if(const ChanceField* chancefield = dynamic_cast<const ChanceField*>(&current_field))
        {
            q_field = "Chance!";
        }
    }
    else if(current_type == TYPE::COMMUNITYCHESTFIELD)
    {
        if(const CommunityChestField* communitychest = dynamic_cast<const CommunityChestField*>(&current_field))
        {
            q_field = "Community chest!";
        }
    }
    else if(current_type == TYPE::JAIL)
    {
        if(const Jail* jail = dynamic_cast<const Jail*>(&current_field))
        {
            q_field = "Jail!";
        }
    }
    else if(current_type == TYPE::INCOMETAX)
    {
        if(const IncomeTax* incometax = dynamic_cast<const IncomeTax*>(&current_field))
        {
            q_field = "Income tax!";
        }
    }
    else if(current_type == TYPE::PARKING)
    {
        if(const Parking* parking = dynamic_cast<const Parking*>(&current_field))
        {
            q_field = "Parking!";
        }
    }
    else if(current_type == TYPE::LUXURYTAX)
    {
        if(const LuxuryTax* luxurytax = dynamic_cast<const LuxuryTax*>(&current_field))
        {
            q_field = "Luxury tax!";
        }
    }
    else if(current_type == TYPE::STARTFIELD)
    {
        if(const StartField* startfield = dynamic_cast<const StartField*>(&current_field))
        {
            q_field = "Start!";
        }
    }
    return q_field;
}

std::pair<int,int> GameController::fieldCoords(int idx) const
{
    return coordinates[idx];
}

QString GameController::currentPlayerToken() const
{
    int current_player_idx = this->_game.getCurrentPlayer();
    Player current_player = this->getPlayer(current_player_idx);
    Token player_token = current_player.getToken();
    std::string player_token_std = str_token_map[player_token];
    QString q_player_token = QString::fromStdString(player_token_std);
    return q_player_token;
}

QString GameController::currentPlayerIndex() const
{
    int current_player_idx = this->_game.getCurrentPlayer();
    QString q_player_idx = QString::number(current_player_idx);
    return q_player_idx;
}

std::vector<Token> GameController::playerTokens() const
{
    std::vector<Token> tokens;
    for(Player player : this->_game.getPlayers())
    {
        tokens.push_back(player.getToken());
    }
    return tokens;
}

int GameController::getCurrentPlayerIndex() const
{
    return this->_game.getCurrentPlayer();
}

void GameController::findNextPlayer()
{
    this->_game.findNextPlayer();
}

void GameController::buyField()
{
    int code = this->_game.buyOwnableField();
    QString q_field = this->currentPlayerField();
    emit triedBuyField(code, q_field);
}