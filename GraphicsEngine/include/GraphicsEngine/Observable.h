#pragma once

#include <functional>
#include <memory>

#include "DllImpExp.h"

namespace graphics_engine
{

    template <typename... Args>
    class Observable {
    public:
        using Callback = std::function<void(Args...)>;

        virtual ~Observable() = default;

        virtual auto AddObserver(Callback callback) -> void = 0;
        virtual auto NotifyObservers(Args... args) -> void = 0;
    };

    template <typename... Args>
    using ObservablePtr = std::unique_ptr<Observable<Args...>>;

}
