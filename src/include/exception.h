//
// Created by 20473 on 2024/7/4.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <iostream>
#include <stdexcept>

namespace FileSystem {
enum class ExceptionType {
  RUNTIME_ERROR = 0,
  OUT_OUT_RANGE = 1,
  FILE_NOT_FOUND = 2,
  SYSTEM_ERROR = 3,
};

static auto ExceptionTypeToString(const ExceptionType type) -> std::string {
  switch (type) {
    case ExceptionType::FILE_NOT_FOUND:
      return "File Not Found.";
    case ExceptionType::SYSTEM_ERROR:
      return "System Error.";
    default:
      return "";
  }
}

class Exception : public std::runtime_error {
 public:
  ExceptionType type_;

  explicit Exception(const ExceptionType type, const std::string &msg, const bool print = true)
      : std::runtime_error(msg), type_(type) {
    if (print) {
      const std::string message = "Message: " + msg + "\n";
      std::cerr << message;
    }
  }
};

class FileNotFoundException : public Exception {
 public:
  FileNotFoundException() = delete;

  explicit FileNotFoundException(const std::string &msg) : Exception(ExceptionType::FILE_NOT_FOUND, msg) {}
};

class SystemExpection : public Exception {
 public:
  SystemExpection() = delete;

  explicit SystemExpection(const std::string &msg) : Exception(ExceptionType::SYSTEM_ERROR, msg) {}
};

class OutOfRangeException : public Exception {
 public:
  OutOfRangeException() = delete;

  explicit OutOfRangeException(const std::string &msg) : Exception(ExceptionType::OUT_OUT_RANGE, msg) {}
};
}  // namespace FileSystem
#endif  // EXCEPTION_H
