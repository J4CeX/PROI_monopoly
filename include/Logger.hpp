#pragma once

#include <iostream>
#include <string>

class Logger {
    protected:
        Logger(unsigned logLevel):
            level_(logLevel) {};

        static Logger* logger_;

        unsigned int level_;

    public:
        Logger(Logger&) = delete;
        void operator=(const Logger&) = delete;

        ~Logger() {
            delete logger_;
        }

        static Logger* getLogger(unsigned int level = 0);

        void log(unsigned int level, const std::string& message) {
            if (level >= level_) {
                std::cout << "A " << level << " message: " << message << std::endl;
            }
        }
};

Logger* Logger::logger_ = nullptr;

Logger* Logger::getLogger(unsigned int level) {
    if (logger_ == nullptr) {
        logger_ = new Logger(level);
    }

    return logger_;
}

