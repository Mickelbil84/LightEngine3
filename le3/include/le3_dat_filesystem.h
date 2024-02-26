#pragma once

#include "le3_dat_archive.h"

namespace le3 {
    struct LE3DatFileNode {
        std::string path, archiveName;
        bool isDirectory;
        std::vector<LE3DatFileNode*> children;
        LE3DatFileNode* parent;
    };

    class LE3DatFileSystem {
    public:
        LE3DatFileSystem();
        ~LE3DatFileSystem();

        void addArchive(std::string archiveName, std::string archivePath);
        
        void appendFile(std::string archiveName, std::string path, LE3DatBuffer fileBuffer, bool shouldCompress = true);
        void appendFile(std::string archiveName, std::string path, std::string filePath, bool shouldCompress = true); // Load from system

        inline void defragmentArchive(std::string archiveName);
        void defragmentArchives();

        std::vector<std::string> getFilesFromDir(std::string dirPath, bool recurse = true);
        LE3DatBuffer getFileContent(std::string filepath, bool shouldDecompress = true);

    private:
        std::map<std::string, LE3DatArchivePtr> m_archives;
        std::vector<std::string> m_archiveNames;

        LE3DatFileNode* m_rootDir;
        std::map<std::string, LE3DatFileNode> m_fileNodes;

        // For some path dir1/dir2/.../dirk/file.ext, add also (recursively) the dirs if they are new
        LE3DatFileNode* addFileNode(std::string path, std::string archiveName, bool isDirectory);
    };
}