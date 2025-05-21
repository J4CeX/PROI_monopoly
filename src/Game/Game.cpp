#include "Game.hpp"

namespace Monopoly {
    Game::Game(size_t playersNumber) {
        turnCounter = 0;
        currentPlayer = 0;
        dice.first = dice.second = 0;

    }

    Game::Game(const Game& secGame) {

    }

    Game::Game(Game&& secGame) {

    }

    Game& Game::operator=(const Game& secGame) {

    }

    Game& Game::operator=(Game&& secGame) {

    }

    Game::~Game() {

    }

    bool Game::canFieldBeBought() {

    }

    void Game::rollDice() {

    }

    bool Game::isFinished() {

    }

    size_t Game::findNextPlayer() {

    }

    bool Game::playerMortgageField(size_t& player, size_t& field, bool unMortgage = false) const {

    }

    bool Game::playerBuysHouse(size_t& player, size_t& field, bool sellsHouse = false) const {

    }

    void Game::buyOwnableField() {

    }

    bool Game::sellOwnableField(size_t& player, size_t& field) {

    }

    size_t Game::movePlayer() {

    }

    void Game::useGetOutOfJailCard() {

    }
}