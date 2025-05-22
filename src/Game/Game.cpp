#include "Game.hpp"

namespace Monopoly {
    Game::Game():
    turnCounter(0), currentPlayer(0), dice(0, 0),
    diceDubletCounter(0) {
        setFields();
        setChances();
        setCommunityChests();
    }

    Game::Game(const Game& secGame) {
        turnCounter = secGame.turnCounter;
        currentPlayer = secGame.currentPlayer;
        dice = secGame.dice;
        diceDubletCounter = secGame.diceDubletCounter;
        players = secGame.players;
        chances = secGame.chances;
        communityChests = secGame.communityChests;
        for (const auto& field: secGame.fields) {
            fields.push_back(field->clone());
        }
    }

    Game::Game(Game&& secGame) {
        turnCounter = secGame.turnCounter;
        currentPlayer = secGame.currentPlayer;
        dice = secGame.dice;
        diceDubletCounter = secGame.diceDubletCounter;
        players = secGame.players;
        chances = secGame.chances;
        communityChests = secGame.communityChests;
        fields = move(secGame.fields);
    }

    Game& Game::operator=(const Game& secGame) {
        if (this != &secGame) {
            turnCounter = secGame.turnCounter;
            currentPlayer = secGame.currentPlayer;
            dice = secGame.dice;
            diceDubletCounter = secGame.diceDubletCounter;
            players = secGame.players;
            chances = secGame.chances;
            communityChests = secGame.communityChests;
            for (const auto& field: secGame.fields) {
                fields.push_back(field->clone());
            }
        }
        return *this;
    }

    Game& Game::operator=(Game&& secGame) {
        if (this != &secGame) {
            turnCounter = secGame.turnCounter;
            currentPlayer = secGame.currentPlayer;
            dice = secGame.dice;
            diceDubletCounter = secGame.diceDubletCounter;
            players = secGame.players;
            chances = secGame.chances;
            communityChests = secGame.communityChests;
            fields = move(secGame.fields);
        }
        return *this;
    }

    bool Game::canFieldBeBought() {

        return true;
    }

    void Game::rollDice() {
        // srand(time(NULL)); TO MUSI BYĆ W GUI !!!
        int first = rand() % 6 + 1;
        int second = rand() % 6 + 1;

        if (first == second) {
            if ((rand() % 6) != 0) {
                do {
                    second = rand() % 6 + 1;
                } while (second == first);
            }
        }
        dice.first = first;
        dice.second = second;
    }



    bool Game::isFinished() {
        int inGame = 0;
        for (const auto& player: players) {
            if (!player.getIsBankrupt()) {
                inGame++;
            }
        }
        return inGame > 1 ? false : true;
    }

    size_t Game::findNextPlayer() {
        currentPlayer = ++currentPlayer % players.size();
        return currentPlayer;
    }

    bool Game::addPlayer(Player& newPlayer) {
        if (players.size() < 4) {
            players.push_back(newPlayer);
            return true;
        }
        else {
            return false;
        }
    }

    bool Game::playerMortgageField(size_t& player, size_t& field, bool unMortgage) const {

        return true;
    }

    bool Game::playerBuysHouse(size_t& player, size_t& field, bool sellsHouse) const {

        return true;
    }

    void Game::buyOwnableField() {

    }

    bool Game::sellOwnableField(size_t& player, size_t& field) {

        return true;
    }

    size_t Game::movePlayer() {

        return 0;
    }

    void Game::useGetOutOfJailCard() {

    }

    void Game::setFields() {
        pushField<StartField>(0);
        pushField<Street>(1, "Konopacka", 60, 2, Color::Brown, 10, 30, 90, 160, 250);
        pushField<CommunityChestField>(2);
        pushField<Street>(3, "Stalowa", 60, 4, Color::Brown, 20, 60, 180, 320, 450);
        pushField<IncomeTax>(4);
        pushField<Station>(5, "Dworzec Zachodni");
        pushField<Street>(6, "Radzymińska", 100, 6, Color::Lightblue, 30, 90, 270, 400, 550);
        pushField<ChanceField>(7);
        pushField<Street>(8, "Jagiellońska", 100, 6, Color::Lightblue, 30, 90, 270, 400, 550);
        pushField<Street>(9, "Targowa", 120, 8, Color::Lightblue, 40, 100, 300, 450, 600);
        pushField<Jail>(10);
        pushField<Street>(11, "Płowiecka", 140, 10, Color::Pink, 50, 150, 450, 625, 750);
        pushField<Utility>(12, "Elektrownia");
        pushField<Street>(13, "Marsa", 140, 10, Color::Pink, 50, 150, 450, 625, 750);
        pushField<Street>(14, "Grochowska", 160, 12, Color::Pink, 60, 180, 500, 700, 900);
        pushField<Station>(15, "Dworzec Gdański");
        pushField<Street>(16, "Obozowa", 180, 14, Color::Orange, 70, 200, 550, 750, 950);
        pushField<CommunityChestField>(17);
        pushField<Street>(18, "Górczewska", 180, 14, Color::Orange, 70, 200, 550, 750, 950);
        pushField<Street>(19, "Wolska", 200, 16, Color::Orange, 80, 220, 600, 800, 1000);
        pushField<Parking>(20);
        pushField<Street>(21, "Mickiewicza", 220, 18, Color::Red, 90, 250, 700, 875, 1050);
        pushField<ChanceField>(22);
        pushField<Street>(23, "Słowackiego", 220, 18, Color::Red, 90, 250, 700, 875, 1050);
        pushField<Street>(24, "Plac Wilsona", 240, 20, Color::Red, 100, 300, 750, 925, 1100);
        pushField<Station>(25, "Dworzec Wschodni");
        pushField<Street>(26, "Świętokrzyska", 260, 22, Color::Yellow, 110, 330, 800, 975, 1150);
        pushField<Street>(27, "Krakowskie Przedmieście", 260, 22, Color::Yellow, 110, 330, 800, 975, 1150);
        pushField<Utility>(28, "Wodociągi");
        pushField<Street>(29, "Nowy Świat", 280, 24, Color::Yellow, 120, 360, 850, 1025, 1200);
        pushField<GoToJail>(30);
        pushField<Street>(31, "Plac Trzech Krzyży", 300, 26, Color::Green, 130, 390, 900, 1100, 1275);
        pushField<Street>(32, "Marszałkowska", 300, 26, Color::Green, 130, 390, 900, 1100, 1275);
        pushField<CommunityChestField>(33);
        pushField<Street>(34, "Aleje Jerozolimskie", 320, 28, Color::Green, 150, 450, 1000, 1200, 1400);
        pushField<Station>(35, "Dworzec Centralny");
        pushField<ChanceField>(36);
        pushField<Street>(37, "Belwederska", 350, 35, Color::Darkblue, 175, 500, 1100, 1300, 1500);
        pushField<LuxuryTax>(38);
        pushField<Street>(39, "Aleje Ujazdowskie", 400, 50, Color::Darkblue, 200, 600, 1400, 1700, 2000);
    }

    void Game::setChances() {
        EventCardContainer generatedChances;
        // ...
        chances = generatedChances;
    }

    void Game::setCommunityChests() {
        EventCardContainer generatedCommunityChests;
        // ...
        communityChests = generatedCommunityChests;
    }

}