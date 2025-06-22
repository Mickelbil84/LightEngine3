#pragma once

#include "core/le3_engine_systems.h"

namespace le3 {
    class LE3EditorComDeleteObjects : public LE3EditorCommand {
    public:
        LE3EditorComDeleteObjects(std::vector<std::string> names);

        virtual void execute();
        virtual void undo();

    private:
        std::vector<std::string> m_names;
        std::vector<double> m_tickets;
    };
}