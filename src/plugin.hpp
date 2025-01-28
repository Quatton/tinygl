#pragma once

#include <memory>

// Forward declaration
class Pipeline;

class PluginBase {
public:
  virtual ~PluginBase() = default;
  virtual void setup(Pipeline &p){};
  virtual void update(Pipeline &p){};
  [[nodiscard]] virtual const std::type_info &type() const {
    return typeid(PluginBase);
  }
};