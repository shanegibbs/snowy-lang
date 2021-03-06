#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#include "Log.h"

namespace Snowy {

FILE *Log::out = stderr;
bool Log::abort_on_fatal = true;
LogLevel Log::log_level = UI;

void Log::setup() {
  char *log_level = getenv("LOG_LEVEL");

  if (log_level) {
    if (strcmp(log_level, "trace") == 0) {
      Snowy::Log::setLogLevel(Snowy::TRACE);
    } else if (strcmp(log_level, "debug") == 0) {
      Snowy::Log::setLogLevel(Snowy::DEBUG);
    } else if (strcmp(log_level, "info") == 0) {
      Snowy::Log::setLogLevel(Snowy::INFO);
    } else if (strcmp(log_level, "warn") == 0) {
      Snowy::Log::setLogLevel(Snowy::WARN);
    } else if (strcmp(log_level, "error") == 0) {
      Snowy::Log::setLogLevel(Snowy::ERROR);
    } else if (strcmp(log_level, "ui") == 0) {
      Snowy::Log::setLogLevel(Snowy::UI);
    } else if (strcmp(log_level, "fatal") == 0) {
      Snowy::Log::setLogLevel(Snowy::FATAL);
    }
  }
}

Log::Log(const char *n) { name = n; }

void Log::log(LogLevel l, const char *format, va_list *args) const {
  char *msg = (char *)malloc(4096);
  vsprintf(msg, format, *args);

  const char *level = "UNKNOWN";

  switch (l) {
    case TRACE:
      level = "TRACE";
      break;

    case DEBUG:
      level = "\x1b[36mDEBUG\x1b[0m";
      break;

    case INFO:
      level = "\x1b[34mINFO\x1b[0m ";
      break;

    case WARN:
      level = "\x1b[33mWARN\x1b[0m ";
      break;

    case ERROR:
      level = "\x1b[31mERROR\x1b[0m";
      break;

    case UI:
      level = "UI";
      break;

    case FATAL:
      level = "\x1b[31mFATAL\x1b[0m";
      break;
  };

  fprintf(out, "** %-5s [%s] - %s\n", level, name, msg);

  free(msg);

  fflush(out);
}

void Log::trace(const char *format, ...) const {
  if (log_level > TRACE) {
    return;
  }

  va_list args;
  va_start(args, format);
  log(TRACE, format, &args);
  va_end(args);
}

void Log::debug(const char *format, ...) const {
  if (log_level > DEBUG) {
    return;
  }

  va_list args;
  va_start(args, format);
  log(DEBUG, format, &args);
  va_end(args);
}

void Log::info(const char *format, ...) const {
  if (log_level > INFO) {
    return;
  }

  va_list args;
  va_start(args, format);
  log(INFO, format, &args);
  va_end(args);
}

void Log::warn(const char *format, ...) const {
  if (log_level > WARN) {
    return;
  }

  va_list args;
  va_start(args, format);
  log(WARN, format, &args);
  va_end(args);
}

void Log::error(const char *format, ...) const {
  if (log_level > ERROR) {
    return;
  }

  va_list args;
  va_start(args, format);
  log(ERROR, format, &args);
  va_end(args);
}

void Log::ui(const char *format, ...) const {
  if (log_level > UI) {
    return;
  }

  char *msg = (char *)malloc(4096);

  va_list args;
  va_start(args, format);

  vsprintf(msg, format, args);
  fprintf(out, "%s\n", msg);

  free(msg);
  fflush(out);

  info(format, &args);
  va_end(args);
}

void Log::fatal(const char *format, ...) const {
  va_list args;
  va_start(args, format);
  log(FATAL, format, &args);
  va_end(args);

  if (abort_on_fatal) {
    fprintf(stderr, "** Aborting on FATAL...\n");
    abort();
  } else {
    throw FatalLogEvent();
  }
}
}
