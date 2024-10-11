#pragma once

#include <string>

namespace le3 {
    class LE3EditorPopup {
    public:
        virtual void init() = 0;
        virtual void update() = 0;

        virtual ~LE3EditorPopup() {}

    protected:
        void lockEngine();
        void unlockEngine();
    };
}