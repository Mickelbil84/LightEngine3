#pragma once

#include "core/le3_engine_systems.h"
#include "scripting/le3_script_bindings.h"

namespace le3 {
    class LE3EditorComPropertyChange : public LE3EditorCommand {
    public:
        LE3EditorComPropertyChange(double ticket) : m_ticket(ticket) {}

        virtual void execute();
        virtual void undo();

        static void registerLua(); // Should be called once, at start of editor

    private:
        double m_ticket;
    };
    
    LOPEN_DECLARE(LE3EditorComPropertyChange);
}