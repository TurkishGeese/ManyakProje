#pragma once

class Logger {
public:
    Logger(const Logger&) = delete;

    static void logError(const char *error);
    static void logSdlError(const char *error);
    static void logSdlImageError(const char *error);
private:
    Logger() = default;

    static Logger& getSingleton();

    void internalLogError(const char *error);
    void internalLogSdlError(const char *error);
    void internalLogSdlImageError(const char *error);
};