#pragma once
#ifndef LOGGER_H
#define LOGGER_H
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <initializer_list>

/**
 * @class Logger
 * @brief Provides functionality to save data in the filesystem.
 * 
 * The Logger class includes static methods for logging messages with different log levels:
 *
 * * verbose, 
 * * debug, 
 * * information, 
 * * warning, 
 * * error, 
 * * data.
 */
class Logger {
public:
    static void SetUpLittleFS();

  /**
     * @brief Logs a warning message.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param message The message to log.
     * @param time The timestamp of the log.
     * @param params Optional parameters to include in the log message. NB! the number of parameters must match the number of {placeholders} in the message! 
     */
  static void Warning(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params = {});

  /**
     * @brief Logs a verbose message.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param message The message to log.
     * @param time The timestamp of the log.
     * @param params Optional parameters to include in the log message. NB! the number of parameters must match the number of {placeholders} in the message! 
     */
  static void Verbose(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params = {});

  /**
     * @brief Logs a debug message.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param message The message to log.
     * @param time The timestamp of the log.
     * @param params Optional parameters to include in the log message. NB! the number of parameters must match the number of {placeholders} in the message! 
     */
  static void Debug(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params = {});

  /**
     * @brief Logs an informational message.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param message The message to log.
     * @param time The timestamp of the log.
     * @param params Optional parameters to include in the log message. NB! the number of parameters must match the number of {placeholders} in the message! 
     */
  static void Information(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params = {});

  /**
     * @brief Logs an error message.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param message The message to log.
     * @param time The timestamp of the log.
     * @param params Optional parameters to include in the log message. NB! the number of parameters must match the number of {placeholders} in the message! 
     */
  static void Error(fs::FS &fs, const char *message, const String &time, std::initializer_list<String> params = {});

  /**
     * @brief Logs a data message without any log level. Note that the path is provided intenrally.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param message The message to log.
     */
  static void Data(fs::FS &fs, const String &message);

private:
  // Path where log files will be stored
  static const String logPath;

  /**
     * @enum ValidLogLevel
     * @brief Enum for the different log levels supported by the Logger class.
     */
  enum class ValidLogLevel {
    Verbose,      ///< Verbose log level (For highly detailed logging)
    Debug,        ///< Debug log level (For debugging purposes)
    Information,  ///< Informational log level (For general messages)
    Warning,      ///< Warning log level (For potential issues)
    Error,        ///< Error log level (For critical issues)
    None          ///< No logging
  };

  /**
     * @brief General log function that writes a log message to the filesystem.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param level The log level (Verbose, Debug, Information, Warning, Error).
     * @param tag A tag identifying the source of the log.
     * @param message The log message.
     * @param time The timestamp of the log.
     * @param params Optional parameters to include in the log message. NB! the number of parameters must match the number of {placeholders} in the message! 
     */
  static void log(fs::FS &fs, ValidLogLevel level, const char *tag, const char *message, const String &time, std::initializer_list<String> params);

  /**
     * @brief Writes a formatted log message to the filesystem.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param path The file path where the log will be written.
     * @param level The log level.
     * @param message The log message.
     * @param params Optional parameters to include in the log message. NB! the number of parameters must match the number of {placeholders} in the message! 
     */
  static void write(fs::FS &fs, const String &path, const String &level, const char *message, std::initializer_list<String> params);

  /**
     * @brief Writes a simple message to the filesystem.
     * 
     * @param fs The filesystem instance to write the log to (LittleFS).
     * @param path The file path where the log will be written.
     * @param message The log message.
     */
  static void write(fs::FS &fs, const String &path, const String &message);

  /**
     * @brief Formats a log message by appending optional parameters.
     * 
     * @param message The base log message.
     * @param params Optional parameters to append to the log message.
     * @return A formatted string containing the message and parameters.
     */
  static String FormatMessage(const char *message, std::initializer_list<String> params);
};

#endif  // LOGGER_H