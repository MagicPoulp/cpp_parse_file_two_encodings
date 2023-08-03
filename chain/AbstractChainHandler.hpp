#pragma once

#include "ChainHandler.hpp"
#include "ChainModel.hpp"

// https://refactoring.guru/design-patterns/chain-of-responsibility/cpp/example
/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class AbstractChainHandler : public ChainHandler {
  /**
   * @var ChainHandler
   */
private:
  ChainHandler *next_handler_;
protected:
  ChainModel model;

 public:
  AbstractChainHandler() : next_handler_(nullptr) {
  }

  void setModel(ChainModel model) {
    this->model = model;
  }

  ChainHandler *SetNext(ChainHandler *handler) override {
    this->next_handler_ = handler;
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // $monkey->setNext($squirrel)->setNext($dog);
    return handler;
  }

  std::string Handle(const std::string& request) override {
    if (this->next_handler_) {
      return this->next_handler_->Handle(request);
    }

    return {};
  }
};
