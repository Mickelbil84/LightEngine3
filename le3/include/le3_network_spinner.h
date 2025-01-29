#pragma once

#include <functional>

#include "le3_object.h"
#include "le3_networking.h"

namespace le3 {
    class LE3NetworkSpinner : public LE3Object {
    public:
        LE3NetworkSpinner();
        virtual void update(float deltaTime);

        void setSend(std::function<LE3NetworkRequest()> send) { m_send = send; }
        void setOnResponse(std::function<void(LE3NetworkRequest)> onResponse) { m_onResponse = onResponse; }

        inline void start() { m_isRunning = true; }
        inline void stop() { m_isRunning = false; }

    protected:
        std::function<LE3NetworkRequest()> m_send;
        std::function<void(LE3NetworkRequest)> m_onResponse;
        LE3NetworkRequest m_request;
        bool m_isRunning;
    };
    using LE3NetworkSpinnerPtr = std::shared_ptr<LE3NetworkSpinner>;
}