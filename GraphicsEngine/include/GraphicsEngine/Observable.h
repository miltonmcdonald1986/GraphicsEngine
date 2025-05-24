#pragma once

#include <functional>
#include <memory>

#include "dll_export.h"

namespace graphics_engine {

template <typename... Args>
class Observable {
 public:
  using Callback = std::function<void(Args...)>;

  Observable(const Observable&) = delete;
  auto operator=(const Observable&) -> Observable& = delete;
  Observable(Observable&&) = delete;
  auto operator=(Observable&&) -> Observable& = delete;

  virtual auto AddObserver(Callback callback) -> void = 0;
  virtual auto NotifyObservers(Args... args) -> void = 0;

 protected:
  Observable() = default;
  virtual ~Observable() = default;
};

template <typename... Args>
using ObservablePtr = std::unique_ptr<Observable<Args...>>;

}  // namespace graphics_engine
