#pragma once

#include "le3_dat_archive.h"

namespace le3 {
    struct LE3DatFileNode {
        std::string path, archiveName;
        std::vector<LE3DatFileNode*> children;
        LE3DatFileNode* parent;
    };

    class LE3DatFileSystem {
    public:
        LE3DatFileSystem();
        ~LE3DatFileSystem();

        inline void addArchive(std::string archiveName, std::string archivePath);
        
        void appendFile(std::string archiveName, std::string path, LE3DatBuffer fileBuffer, bool shouldCompress = true);
        void appendFile(std::string archiveName, std::string path, std::string filePath, bool shouldCompress = true); // Load from system

        inline void defragmentArchive(std::string archiveName);
        void defragmentArchives();

    private:
        std::map<std::string, LE3DatArchivePtr> m_archives;
        std::vector<std::string> m_archiveNames;
    };
}