#pragma once

#include "core/le3_engine_systems.h"

namespace le3 {
    class LE3EditorComAddMesh : public LE3EditorCommand { 
    public:
        LE3EditorComAddMesh(std::string name, std::string path, bool isSkeletal);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_name, m_path;
        bool m_bIsSkeletal;
    };
}