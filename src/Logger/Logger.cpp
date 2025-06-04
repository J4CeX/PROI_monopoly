#include <sstream>
#include <chrono>
#include <iomanip>

#include "Logger.hpp"

std::string Logger::logFilename() const {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm utc_tm = *std::gmtime(&now_c);

    std::ostringstream oss;
    oss << "log_"
        << std::put_time(&utc_tm, "%Y-%m-%d_%H-%M-%S")
        << ".txt";
    return oss.str();
}
