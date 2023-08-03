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
  ChainHandler *next_handler_ = nullptr;
protected:
  ChainModel* pModel = nullptr;

 public:
  AbstractChainHandler() : next_handler_(nullptr) {
  }

  void setModel(ChainModel& model) {
    this->pModel = &model;
  }

  ChainHandler *setNext(ChainHandler *handler) override {
    this->next_handler_ = handler;
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // $monkey->setNext($squirrel)->setNext($dog);
    return handler;
  }

  std::string handle(const std::string& request) override {
    if (this->next_handler_) {
      return this->next_handler_->handle(request);
    }

    return {};
  }
};
