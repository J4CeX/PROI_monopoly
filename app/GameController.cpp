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

using namespace Monopoly;
using namespace MonopolyPlayer;

GameController::GameController(QObject *parent): QObject(parent) { }

bool GameController::loadGame()
{
    Game loadedGame;
    int code = loadedGame.load();
    if(code) this->_game = loadedGame;
    return code;
}

bool GameController::saveGame()
{
    int code = this->_game.save();
    return code;
}

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
    this->_newestPlayerId = 1;
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
    Player player = this->getPlayer(this->_game.getCurrentPlayerId()-1);
    int old_bal = player.getBalance(), old_pos = player.getPosition();
    this->_game.rollDice();
    this->_playerMoved = 1;
    player = this->getPlayer(this->_game.getCurrentPlayerId()-1);
    int new_bal = player.getBalance(), new_pos = player.getPosition();
    if(old_bal != new_bal)
    {
        if(new_pos < old_pos) emit currentEvent("Przeszedłeś przez start. Otrzymujesz 200zł!");
    }

    int r1 = _game.getDice().first, r2 = _game.getDice().second;
    std::string results = std::to_string(r1) + " " + std::to_string(r2); 
    QString q_results = QString::fromStdString(results);
    
    emit rolledDice(q_results);
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
    int current_player_idx = this->_game.getCurrentPlayerId()-1;
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
    int current_player_idx = this->_game.getCurrentPlayerId()-1;
    Player current_player = this->getPlayer(current_player_idx);
    int player_balance = current_player.getBalance();
    QString q_player_balance = QString::number(player_balance);
    return q_player_balance;
    
}

QString GameController::currentPlayerPosition() const
{
    int current_player_idx = this->_game.getCurrentPlayerId()-1;
    Player current_player = this->getPlayer(current_player_idx);
    int player_pos = current_player.getPosition();
    QString q_player_pos = QString::number(player_pos);
    return q_player_pos;
}

std::vector<std::pair<QString, size_t>> GameController::playerOwnedFields(int idx) const
{
    std::vector<std::pair<QString, size_t>> result;
    const auto& fields = this->_game.getFields();

    for (const auto& field : fields)
    {
        TYPE type = field->getInfo();
        if (type == TYPE::STREET || type == TYPE::STATION || type == TYPE::UTILITY)
        {
            if (OwnableField* ownableField = dynamic_cast<OwnableField*>(field.get()))
            {
                if (ownableField->isOwned() && ownableField->getOwner() == idx)
                {
                    QString name = QString::fromStdString(ownableField->getName());
                    int position = ownableField->getPosition();
                    QString label = name + "(" + QString::number(position) + ")";
                    result.emplace_back(label, position);
                }
            }
        }
    }

    return result;
}

QString GameController::getGameTurn() const
{
    int turn = this->_game.getTurnCounter() + 1;
    QString q_turn = QString::number(turn);
    return q_turn;
}

std::vector<std::pair<QString, size_t>> GameController::currentPlayerOwnedFields() const
{
    int idx = this->_game.getCurrentPlayerId()-1;
    return this->playerOwnedFields(idx);
}

QString GameController::currentPlayerField()
{
    int idx = this->_game.getCurrentPlayerId()-1;
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
            if(!ownablefield->isOwned()) emit isBuyableField(true, cost, q_field);
            else
            {
                emit isBuyableField(false, cost, q_field);
                if(idx != ownablefield->getOwner() && this->_playerMoved)
                {
                    Player owner = this->getPlayer(ownablefield->getOwner());
                    std::string oName = owner.getName();
                    int rent = ownablefield->getRent();
                    std::string msg = "Trafiłeś na pole gracza " + oName + " - płacisz czynsz w wysokości " + std::to_string(rent) + "zł!";
                    emit currentEvent(QString::fromStdString(msg));
                }
            }
        }
    }
    else if(current_type == TYPE::CHANCEFIELD)
    {
        if(const ChanceField* chancefield = dynamic_cast<const ChanceField*>(&current_field))
        {
            q_field = "Chance!";
            if(this->_playerMoved)
            {
                EventCard event = this->_game.getCurrentEvent();
                std::string event_txt = event.getText();
                emit currentEvent(QString::fromStdString(event_txt));
            }
        }
    }
    else if(current_type == TYPE::COMMUNITYCHESTFIELD)
    {
        if(const CommunityChestField* communitychest = dynamic_cast<const CommunityChestField*>(&current_field))
        {
            q_field = "Community chest!";
            if(this->_playerMoved)
            {
                EventCard event = this->_game.getCurrentEvent();
                std::string event_txt = event.getText();
                emit currentEvent(QString::fromStdString(event_txt));
            }
        }
    }
    else if(current_type == TYPE::JAIL)
    {
        if(const Jail* jail = dynamic_cast<const Jail*>(&current_field))
        {
            q_field = "Jail!";
            if(this->_playerMoved)
            {
                int jailRounds = current_player.getInJailRounds();
                if(jailRounds)
                {
                    if(jailRounds==3) emit currentEvent("Trafiłeś do więzienia! Poczekaj 3 tury lub wyrzuć dublet.");
                    else emit currentEvent("Jesteś w więzieniu. Poczekaj " + QString::number(jailRounds) + " tury lub wyrzuć dublet.");
                }
                else emit currentEvent("Odwiedzasz więzienie.");
            }
        }
    }
    else if(current_type == TYPE::INCOMETAX)
    {
        if(const IncomeTax* incometax = dynamic_cast<const IncomeTax*>(&current_field))
        {
            q_field = "Income tax!";
            if(this->_playerMoved) emit currentEvent("Podatek dochodowy! Płacisz 200zł.");
        }
    }
    else if(current_type == TYPE::PARKING)
    {
        if(const Parking* parking = dynamic_cast<const Parking*>(&current_field))
        {
            q_field = "Parking!";
            if(this->_playerMoved) emit currentEvent("Bezpłatny parking.");
        }
    }
    else if(current_type == TYPE::LUXURYTAX)
    {
        if(const LuxuryTax* luxurytax = dynamic_cast<const LuxuryTax*>(&current_field))
        {
            q_field = "Luxury tax!";
            if(this->_playerMoved) emit currentEvent("Podatek od zbytku! Płacisz 100zł.");
        }
    }
    else if(current_type == TYPE::STARTFIELD)
    {
        if(const StartField* startfield = dynamic_cast<const StartField*>(&current_field))
        {
            q_field = "Start!";
            if(this->_playerMoved) emit currentEvent("Witamy na starcie!");
        }
    }
    return q_field;
}

QStringList GameController::getOwnedFieldInfo(int position)
{
    const auto& fields = this->_game.getFields();
    const auto& field = *(fields[position]); // zakładamy, że position jest poprawne
    TYPE type = field.getInfo();

    QString name = "Unknown";
    QString pos_str = QString::number(position);
    QString type_str = "UNKNOWN";
    QString house_count = "doesn't apply";
    QString rent = "Unknown";
    QString is_mortgaged = "Unknown mortgage status";

    if (const OwnableField* ownable = dynamic_cast<const OwnableField*>(&field))
    {
        name = QString::fromStdString(ownable->getName());
        rent = QString::number(ownable->getRent()) + " zł";
        if(ownable->isMortgaged()) is_mortgaged = "Yes";
        else is_mortgaged = "No";

        if (type == TYPE::STREET)
        {
            type_str = "STREET";
            if (const Street* street = dynamic_cast<const Street*>(ownable))
            {
                house_count = QString::number(street->getHouseCount());
            }
        }
        else if (type == TYPE::STATION)
        {
            type_str = "STATION";
        }
        else if (type == TYPE::UTILITY)
        {
            type_str = "UTILITY";
        }
    }

    return { name, pos_str, type_str, house_count, rent, is_mortgaged };
}

int GameController::buyOfHouse(int pos)
{
    size_t player_id = this->_game.getCurrentPlayerId()-1;
    size_t field_id = static_cast<size_t>(pos);
    int code = this->_game.playerBuyHouse(player_id, field_id);
    return code;
}

int GameController::sellOfHouse(int pos)
{
    size_t player_id = this->_game.getCurrentPlayerId()-1;
    size_t field_id = static_cast<size_t>(pos);
    int code = this->_game.playerBuyHouse(player_id, field_id, true);
    return code;
}

int GameController::ofMortgage(int pos)
{
    size_t player_id = this->_game.getCurrentPlayerId()-1;
    size_t field_id = static_cast<size_t>(pos);
    int code = this->_game.playerMortgageField(player_id, field_id, false);
    return code;
}

int GameController::ofUnmortgage(int pos)
{
    size_t player_id = this->_game.getCurrentPlayerId()-1;
    size_t field_id = static_cast<size_t>(pos);
    int code = this->_game.playerMortgageField(player_id, field_id, true);
    return code;
}

QString GameController::currentPlayerToken() const
{
    int current_player_idx = this->_game.getCurrentPlayerId()-1;
    Player current_player = this->getPlayer(current_player_idx);
    Token player_token = current_player.getToken();
    std::string player_token_std = str_token_map[player_token];
    QString q_player_token = QString::fromStdString(player_token_std);
    return q_player_token;
}

QString GameController::currentPlayerIndex() const
{
    int current_player_idx = this->_game.getCurrentPlayerId()-1;
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
    return this->_game.getCurrentPlayerId()-1;
}

void GameController::findNextPlayer()
{
    this->_playerMoved = 0;
    this->_game.findNextPlayer();
    if(this->_game.getIsFinished())
    {
        int winner_id = this->_game.getCurrentPlayerId()-1;
        Player winner = this->getPlayer(winner_id);
        this->finishedGame(winner);
    }
}

void GameController::buyField()
{
    int code = this->_game.buyOwnableField();
    QString q_field = this->currentPlayerField();
    emit triedBuyField(code, q_field);
}

void GameController::finishedGame(Player winner)
{
    emit finishedGameSignal(QString::fromStdString(winner.getName()));
}