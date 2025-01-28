#pragma once

#include <memory>

// Forward declaration
class Pipeline;

class PluginBase {
public:
  virtual ~PluginBase() = default;
  virtual void setup([[maybe_unused]] Pipeline &p){};
  virtual void update([[maybe_unused]] Pipeline &p){};
  [[nodiscard]] virtual const std::type_info &type() const {
    return typeid(PluginBase);
  };
};