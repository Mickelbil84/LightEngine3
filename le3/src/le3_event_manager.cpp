#include "le3_event_manager.h"
using namespace le3;

void LE3EventManager::subscribe(std::string event, LE3ObjectPtr subscriber, std::function<void(void*)> callback) {
    m_subscriptions[event].push_back({ subscriber, callback });
}
void LE3EventManager::unsubscribe(std::string event, LE3ObjectPtr subscriber) {
    for (auto& subscription : m_subscriptions[event]) {
        if (auto subscriber = subscription.subscriber.lock()) {
            subscription.wantsUnsubscribe = true;
        }
    }
}
void LE3EventManager::notify(std::string event, void* data) {
    for (auto& subscription : m_subscriptions[event]) {
        if (auto subscriber = subscription.subscriber.lock()) {
            subscription.callback(data);
        }
    }
}

void LE3EventManager::applyUnsubscribes() {
    for (auto& pair : m_subscriptions) {
        auto& subscriptions = pair.second;
        subscriptions.erase(std::remove_if(subscriptions.begin(), subscriptions.end(), [](LE3EventSubscription& subscription) {
            return subscription.wantsUnsubscribe || !subscription.subscriber.lock();
        }), subscriptions.end());
    }
}