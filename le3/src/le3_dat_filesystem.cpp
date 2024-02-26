#include "le3_dat_filesystem.h"
using namespace le3;

#include <stdexcept>

#include <fmt/core.h>

#include <queue>

LE3DatFileSystem::LE3DatFileSystem() {
    m_fileNodes[""] = LE3DatFileNode();
    m_rootDir = &m_fileNodes[""];
    m_rootDir->archiveName = "";
    m_rootDir->parent = nullptr;
    m_rootDir->isDirectory = true;
    m_rootDir->path = "";
}
LE3DatFileSystem::~LE3DatFileSystem() {
    m_archives.clear();
}

void LE3DatFileSystem::addArchive(std::string archiveName, std::string archivePath) {
    m_archives[archiveName] = std::move(std::make_unique<LE3DatArchive>(archivePath));
    m_archiveNames.push_back(archiveName);

    for (auto [path, fileInfo] : m_archives[archiveName]->getFileInfos()) {
        addFileNode(path, archiveName, false);
    }
}

void LE3DatFileSystem::appendFile(std::string archiveName, std::string path, LE3DatBuffer fileBuffer, bool shouldCompress) {
    m_archives[archiveName]->appendFile(path, fileBuffer, shouldCompress);
    addFileNode(path, archiveName, false);
}
void LE3DatFileSystem::appendFile(std::string archiveName, std::string path, std::string filePath, bool shouldCompress) {
    LE3DatBuffer buffer = LE3DatBuffer::loadFromSystem(filePath, !shouldCompress);
    appendFile(archiveName, path, buffer, shouldCompress);
}

void LE3DatFileSystem::defragmentArchive(std::string archiveName) {
    m_archives[archiveName]->defragmentArchive();
}

void LE3DatFileSystem::defragmentArchives() {
    for (auto archiveName : m_archiveNames) defragmentArchive(archiveName);
}

LE3DatFileNode* LE3DatFileSystem::addFileNode(std::string path, std::string archiveName, bool isDirectory) {
    if (m_fileNodes.contains(path)) return &m_fileNodes[path];

    auto lastIdx = path.find_last_of('/');
    std::string parentPath = path.substr(0, lastIdx);
    LE3DatFileNode* parent = addFileNode(parentPath, "", true);

    LE3DatFileNode fileNode;
    fileNode.path = path; fileNode.archiveName = archiveName;
    fileNode.isDirectory = isDirectory;
    fileNode.parent = parent;
    m_fileNodes[path] = fileNode;
    parent->children.push_back(&m_fileNodes[path]);

    return &m_fileNodes[path];
}

std::vector<std::string> LE3DatFileSystem::getFilesFromDir(std::string dirPath, bool recurse) {
    std::vector<std::string> res;
    if (!m_fileNodes.contains(dirPath)) throw std::runtime_error(fmt::format("Directory '{}' does not exist in any archive", dirPath));
    if (!m_fileNodes[dirPath].isDirectory) return res;

    if (!recurse) {
        for (auto child : m_fileNodes[dirPath].children)
            if (!child->isDirectory) res.push_back(child->path);
        return res;
    }

    std::queue<std::string> dirQueue;
    dirQueue.push(dirPath);

    while (dirQueue.size() > 0) {
        std::string curr = dirQueue.front(); dirQueue.pop();
        if (!m_fileNodes[curr].isDirectory) {
            res.push_back(curr); continue;
        }
        for (auto child : m_fileNodes[curr].children) dirQueue.push(child->path);
    }
    return res;
}

LE3DatBuffer LE3DatFileSystem::getFileContent(std::string filepath, bool shouldDecompress) {
    if (!m_fileNodes.contains(filepath)) throw std::runtime_error(fmt::format("File '{}' does not exist in any archive", filepath));
    return m_archives[m_fileNodes[filepath].archiveName]->getFileContent(filepath, shouldDecompress);
}