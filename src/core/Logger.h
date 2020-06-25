#pragma once

#include <string>
using std::string;

enum LogLevel
{
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG
};

class Logger
{
public:
    explicit Logger(const string& tag);

    static Logger create(const string& tag);
    void logf(const LogLevel level, string message, ...) const;

private:
    const string tag;
};