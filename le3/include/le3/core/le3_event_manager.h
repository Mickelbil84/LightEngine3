#pragma once

#include <map>
#include <vector>
#include <functional>

#include "core/le3_object.h"

namespace le3 {

    // Note that the callback should never store the (void*)data, since it is not guaranteed to be valid after the function call
    struct LE3EventSubscription {
        LE3ObjectWeakPtr subscriber;
        std::function<void(void*)> callback;
        bool wantsUnsubscribe = false;
    };

    class LE3EventManager {
    public:
        void reset();

        void subscribe(std::string event, LE3ObjectPtr subscriber, std::function<void(void*)> callback);
        void unsubscribe(std::string event, LE3ObjectPtr subscriber); // Lazy unsubscribe
        void notify(std::string event, void* data);

        // This is called internally by the engine, at `le3_application.cpp`
        void applyUnsubscribes();

    private:
        std::map<std::string, std::vector<LE3EventSubscription>> m_subscriptions;
    };

    #define ADD_EVENT(event) \
        static const std::string event = #event;

}