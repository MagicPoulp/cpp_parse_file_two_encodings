#pragma once

// https://refactoring.guru/design-patterns/chain-of-responsibility/cpp/example
/**
 * The Handler interface declares a method for building the chain of handlers.
 * It also declares a method for executing a request.
 */
class ChainHandler {
 public:
  virtual ChainHandler *setNext(ChainHandler *handler) = 0;
  virtual std::string handle(const std::string& request) = 0;
};
