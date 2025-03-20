#pragma once

#include "core/le3_engine_systems.h"

namespace le3 {
    class LE3EditorComReparent : public LE3EditorCommand {
    public:
        LE3EditorComReparent(std::vector<std::string> names);

        virtual void execute();
        virtual void undo();

    private:
        std::vector<std::string> m_names;
        std::map<std::string, std::string> m_oldParents;
        std::map<std::string, glm::mat4> m_oldTransforms;
    };
}