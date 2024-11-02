#pragma once

#include "le3_engine_systems.h"

namespace le3 {
    class LE3EditorComDeleteMesh : public LE3EditorCommand { 
    public:
        LE3EditorComDeleteMesh(std::string name, std::string path, bool isSkeletal);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_name, m_path;
        bool m_bIsSkeletal;
        std::map<std::string, LE3AnimationTrack> m_animationTracks;
        std::vector<std::pair<std::string, std::string>> m_depObjects;
    };
}