#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char *log_level_to_string(enum LogLevel level) {
  switch (level) {
  case FATAL:
    return "FATAL";
  case ERROR:
    return "ERROR";
  case WARN:
    return "WARN";
  case INFO:
    return "INFO";
  case DEBUG:
    return "DEBUG";
  case TRACE:
    return "TRACE";
  default:
    return "UNKNOWN";
  }
}

static void current_time(char *buffer, size_t size) {
  time_t now = time(NULL);

  struct tm tm;
  localtime_r(&now, &tm);

  strftime(buffer, size, "%Y/%m/%d %H:%M:%S", &tm);
}

void logger(const char *message, enum LogLevel level) {
  char timestamp[20];

  current_time(timestamp, sizeof(timestamp));

  fprintf(stdout, "%s [%s] %s\n", timestamp, log_level_to_string(level),
          message);

  if (level == FATAL)
    exit(EXIT_FAILURE);
}
