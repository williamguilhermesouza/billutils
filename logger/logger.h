#ifndef LOGGER_H
#define LOGGER_H

/**
 * Severity of a log message.
 */
enum LogLevel {
  /** Critical error. Program terminates. */
  FATAL,
  /** Recoverable error. */
  ERROR,
  /** Warning. */
  WARN,
  /** Informational message. */
  INFO,
  /** Debug message. */
  DEBUG,
  /** Very verbose diagnostic output. */
  TRACE
};

/**
 * @brief Writes a message to the log.
 *
 * Prints the current timestamp, log level, and message to stdout.
 * If the log level is FATAL, the process terminates with EXIT_FAILURE.
 *
 * @param message The message to log.
 * @param level The severity of the message.
 */
void logger(const char *message, enum LogLevel level);

/** Logs a fatal error and terminates the application. */
#define LOG_FATAL(msg) logger(msg, FATAL)
/** Logs an error message. */
#define LOG_ERROR(msg) logger(msg, ERROR)
/** Logs a warning message. */
#define LOG_WARN(msg) logger(msg, WARN)
/** Logs an informational message. */
#define LOG_INFO(msg) logger(msg, INFO)
/** Logs a debug message. */
#define LOG_DEBUG(msg) logger(msg, DEBUG)
/** Logs a trace message. */
#define LOG_TRACE(msg) logger(msg, TRACE)

#endif
