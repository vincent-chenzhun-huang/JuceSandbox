#include "../Utils/Logger.h"

SandboxLogger::SandboxLogger() : logLevel(LOGGER_DEBUG), currentLogLevel(LOGGER_SYSTEM)
{}

SandboxLogger::~SandboxLogger()
{}

void SandboxLogger::setLevelThreshold(LogLevel level)
{
    logLevel = level;
}

void SandboxLogger::setCurrentLevel(LogLevel level)
{
    currentLogLevel = level;
}

void SandboxLogger::logMessage(const juce::String& message)
{
    // include the timestamp and the log level string in the message
    auto timestamp = juce::Time::getCurrentTime().formatted("%Y-%m-%d %H:%M:%S");
    auto levelString = getLevelString(currentLogLevel);

    auto logMessage = timestamp + " [" + levelString + "] " + message;
    std::cout << logMessage << std::endl;
}

void SandboxLogger::log(const juce::String& message, LogLevel level)
{
    if (level >= logLevel)
    {
        lock.enter();
        LogLevel originalLevel = logLevel;
        setCurrentLevel(level);
        logMessage(message);
        setCurrentLevel(originalLevel); // set back to the level threshold
        lock.exit();
    }
}

juce::String SandboxLogger::getLevelString(LogLevel level)
{
    switch (level)
    {
        case LOGGER_SYSTEM:
            return "SYSTEM";
        case LOGGER_DEBUG:
            return "DEBUG";
        case LOGGER_INFO:
            return "INFO";
        case LOGGER_WARN:
            return "WARN";
        case LOGGER_ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}
