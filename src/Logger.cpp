#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <FS.h>
#include "Logger.h"

// Path to the log file stored in the filesystem
const String Logger::logPath = "/log.txt";

// Enum for the different log levels supported by the Logger class.
enum class ValidLogLevel
{
    Verbose,     ///< Verbose log level (For highly detailed logging)
    Debug,       ///< Debug log level (For debugging purposes)
    Information, ///< Informational log level (For general messages)
    Warning,     ///< Warning log level (For potential issues)
    Error,       ///< Error log level (For critical issues)
    None         ///< No logging
};

ValidLogLevel CurrentLogLevel = ValidLogLevel::Debug;

// Formats a log message by appending optional parameters.
String Logger::FormatMessage(const char *message, std::initializer_list<String> params)
{
    String formattedMessage = message;
    size_t paramIndex = 0;

    for (const auto &param : params)
    {
        String placeholder = "{" + String(paramIndex) + "}";
        int placeholderIndex = formattedMessage.indexOf(placeholder);

        if (placeholderIndex == -1)
            break;

        formattedMessage.replace(placeholder, param);
        paramIndex++;
    }

    if (formattedMessage.indexOf("{") != -1)
    {
        return "Error: Logger: Mismatched placeholders and parameters";
    }

    return formattedMessage;
}

// Writes a formatted log message to the filesystem.
void Logger::write(fs::FS &fs, const String &path, const String &level, const char *message, std::initializer_list<String> params)
{
    String logEntry = level + ": " + FormatMessage(message, params) + "\n";
    Serial.print(logEntry);
    Logger::write(fs, path, logEntry);
}

// Writes a simple message to the filesystem.
void Logger::write(fs::FS &fs, const String &path, const String &message)
{
    const char *mode = fs.exists(path) ? "a" : "w";
    File file = fs.open(path, mode);

    if (!file)
    {
        Serial.print(mode == "w" ? "Failed to create file: " : "Failed to open file: ");
        Serial.println(path);
        Serial.println(message);
        return;
    }
    else if (mode == "w")
    {
        Serial.print("Successfully created file: ");
        Serial.println(path);
    }

    file.println(message);
    file.close();
}

// General log function that writes a log message to the filesystem.
void Logger::log(fs::FS &fs, ValidLogLevel level, const char *tag, const char *message, const String &time, std::initializer_list<String> params)
{
    if (static_cast<int>(level) >= static_cast<int>(CurrentLogLevel))
    {
        String logPrefix = "[" + time + " " + tag + "]";
        write(fs, logPath, logPrefix, message, params);
    }
}

// log a warning
void Logger::Warning(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params)
{
    log(fs, ValidLogLevel::Warning, "WAR", message, time, params);
}

// log a verbose message
void Logger::Verbose(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params)
{
    log(fs, ValidLogLevel::Verbose, "VER", message, time, params);
}

// log a debug message
void Logger::Debug(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params)
{
    log(fs, ValidLogLevel::Debug, "DEB", message, time, params);
}

// log an information message
void Logger::Information(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params)
{
    log(fs, ValidLogLevel::Information, "INF", message, time, params);
}

// log an error
void Logger::Error(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params)
{
    log(fs, ValidLogLevel::Error, "ERR", message, time, params);
}

// write data to the data file
void Logger::Data(fs::FS &fs, const String &message)
{
    write(fs, "/data.txt", message);
}

void Logger::SetUpLittleFS()
{
    if (!LittleFS.begin())
    {
        Serial.println("An error has occurred while mounting LittleFS");
    }
    else
    {
        Serial.println("LittleFS mounted successfully");
    }
}
