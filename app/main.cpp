#include <iostream>

#include <fstream>

#include "../include/Game.hpp"
#include "Logger.hpp"

using namespace Monopoly;

int main() {
	std::ofstream logFile(logFilename());
	std::cout.rdbuf(logFile.rdbuf());

    std::cout << "before" << std::endl;
    Game game;
    std::cout << "after" << std::endl;
    return 0;
}