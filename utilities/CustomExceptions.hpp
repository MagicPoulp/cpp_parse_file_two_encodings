#pragma once
#include <exception>
#include <string>

class CustomExceptions : public std::exception {
private:
  std::string message;

public:
  CustomExceptions(std::string msg) : message(msg) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};

class DetailedErrorCustomException : public CustomExceptions {
public:
  DetailedErrorCustomException(std::string msg)
    : CustomExceptions(msg)
  {}
};
