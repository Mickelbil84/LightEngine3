#pragma once

#include "le3_model.h"

namespace le3 {
    class LE3AssetManager {
    public:
        void init();

        inline LE3ScreenRectPtr getScreenRect() { return m_screenRect; }


    private:
        LE3ScreenRectPtr m_screenRect = nullptr; // Create this crucial geometry only once
    }; 
}