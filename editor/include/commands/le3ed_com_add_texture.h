#pragma once

#include "le3_engine_systems.h"

namespace le3 {
    class LE3EditorComAddTexture : public LE3EditorCommand { 
    public:
        LE3EditorComAddTexture(std::string name, std::string path, bool interpolate);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_name, m_path;
        bool m_bInterpolate;
    };
}