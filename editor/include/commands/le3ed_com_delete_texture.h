#pragma once

#include "le3_engine_systems.h"

namespace le3 {
    class LE3EditorComDeleteTexture : public LE3EditorCommand { 
    public:
        LE3EditorComDeleteTexture(std::string name, std::string path, bool interpolate);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_name, m_path;
        bool m_bInterpolate;
        std::vector<std::string> 
            m_depMatsDiff, m_depMatsSpec, m_depMatsNorm, m_depMatsCube; // Bookkeeping for undo
    };
}