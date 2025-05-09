#pragma once

#include "Observable.h"

namespace GraphicsEngine
{

    template <typename... Args>
    class ObservableImpl : public Observable<Args...>
    {

    public:

        auto AddObserver(
            typename Observable<Args...>::Callback callback
        ) -> void override
        {
            m_Observers.push_back(callback);
        }

        auto NotifyObservers(
            Args... args
        ) -> void override
        {
            for (const auto& fnObserver : m_Observers)
            {
                fnObserver(args...);
            }
        }

    private:

        std::vector<typename Observable<Args...>::Callback> m_Observers;
    };

    template<typename... Args>
    using ObservableImplPtr = std::unique_ptr<ObservableImpl<Args...> >;

    template <typename... Args>
    auto CreateObservable() -> ObservableImplPtr<Args...>
    {
        return std::make_unique<ObservableImpl<Args...>>();
    }

}
