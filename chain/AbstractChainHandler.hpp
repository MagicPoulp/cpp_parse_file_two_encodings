#pragma once

#include "ChainHandler.hpp"

// https://refactoring.guru/design-patterns/chain-of-responsibility/cpp/example
/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class AbstractChainHandler : public ChainHandler {
  /**
   * @var Handler
   */
 private:
  ChainHandler *next_handler_;

 public:
  AbstractChainHandler() : next_handler_(nullptr) {
  }

  ChainHandler *SetNext(ChainHandler *handler) override {
    this->next_handler_ = handler;
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // $monkey->setNext($squirrel)->setNext($dog);
    return handler;
  }

  std::string Handle(std::string request) override {
    if (this->next_handler_) {
      return this->next_handler_->Handle(request);
    }

    return {};
  }
};
