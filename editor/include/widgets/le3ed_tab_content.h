#pragma once

#include <le3.h>

namespace le3 {
    class LE3EditorTabContent {
    public:
        void init();
        void update();

    private:
        void updateArchiveList();
        void updateTreeView();

        void recurseContentTree(LE3DatFileNode* node);
        static std::string formatSize(uint64_t size);
        
        ImGuiTableFlags flags;
        int m_selectedArchive;
        std::vector<std::string> m_archives;
        std::map<std::string, bool> m_openStatus;

        bool m_bShowEngineContent = false;
        bool m_bShowDemoContent = false;
    };
}