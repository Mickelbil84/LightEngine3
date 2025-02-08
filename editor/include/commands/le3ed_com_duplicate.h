#pragma once

#include "le3_engine_systems.h"

namespace le3 {
    class LE3EditorComDuplicate : public LE3EditorCommand {
    public:
        LE3EditorComDuplicate(std::vector<std::string> names);

        virtual void execute();
        virtual void undo();

    private:
        std::vector<std::string> m_names, m_newNames;
    };
}