#pragma once

#include "le3_engine_systems.h"

namespace le3 {
    class LE3EditorComReparent : public LE3EditorCommand {
    public:
        LE3EditorComReparent(std::string objName, std::string newParentName);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_objName, m_newParentName, m_oldParentName;
    };
}