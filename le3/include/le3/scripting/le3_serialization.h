#pragma once

#include <string>

namespace le3 {
    class LE3Serialization {
    public:
        // Dump a (flat) Lua table to a file (should end with *.lua)
        // Note that the table should be a top-level global Lua variable
        static void dump(std::string table, std::string filename);
    };
}