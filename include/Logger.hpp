#pragma once

#include <iostream>
#include <string>

class Logger {
    private:
        unsigned int level_;
        unsigned int count_;

    public:
        Logger(unsigned logLevel):
            level_(logLevel) {};


        Logger(Logger&) = delete;
        void operator=(const Logger&) = delete;

        ~Logger() = default;

        template <typename T>
        void log(unsigned int level, const T& message,
            const char* name, unsigned int line) {
            count_ += 1;

            if (level >= level_) {
                std::cout << count_;
                if (level == 0) { std::cout << " [debug] "; }
                else if (level == 1) { std::cout << "  [info] "; }
                else if (level == 2) { std::cout << "  [warn] "; }
                else if (level == 3) { std::cout << " [error] "; }
                else if (level >= 4) { std::cout << "  [crit] "; }
                std::cout << "@ " << name << ":" << line << ": " << message << std::endl;
            }
        }
};


inline Logger& logger() {
    static Logger logger(0);
    return logger;
}

#define LOG(level, message_) \
    logger().log( \
        level, \
        message_, \
        __func__, \
        __LINE__ \
    );

