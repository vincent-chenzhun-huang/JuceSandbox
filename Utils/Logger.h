#pragma once

#include <JuceHeader.h>



class SandboxLogger : public juce::Logger
{
    public:
        enum LogLevel 
        {
            LOGGER_SYSTEM,
            LOGGER_DEBUG,
            LOGGER_INFO,
            LOGGER_WARN,
            LOGGER_ERROR,
        };
        SandboxLogger();
        ~SandboxLogger() override;

        void setLevelThreshold(LogLevel level);
        void setCurrentLevel(LogLevel level);
        void logMessage(const juce::String& message) override;

        void log(const juce::String& message, LogLevel level);
        juce::String getLevelString(LogLevel level);
    private:
        // add a lock to prevent multiple threads from writing to the console at the same time
        juce::CriticalSection lock;
        LogLevel logLevel;
        LogLevel currentLogLevel;
};