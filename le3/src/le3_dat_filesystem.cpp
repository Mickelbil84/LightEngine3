#include "le3_dat_filesystem.h"
using namespace le3;

LE3DatFileSystem::LE3DatFileSystem() {
}
LE3DatFileSystem::~LE3DatFileSystem() {
    m_archives.clear();
}

void LE3DatFileSystem::addArchive(std::string archiveName, std::string archivePath) {
    m_archives[archiveName] = std::move(std::make_unique<LE3DatArchive>(archivePath));
    m_archiveNames.push_back(archiveName);
}

void LE3DatFileSystem::appendFile(std::string archiveName, std::string path, LE3DatBuffer fileBuffer, bool shouldCompress) {
    m_archives[archiveName]->appendFile(path, fileBuffer, shouldCompress);
}
void LE3DatFileSystem::appendFile(std::string archiveName, std::string path, std::string filePath, bool shouldCompress) {
    LE3DatBuffer buffer; buffer.loadFromSystem(filePath, !shouldCompress);
    appendFile(archiveName, path, buffer, shouldCompress);
}

void LE3DatFileSystem::defragmentArchive(std::string archiveName) {
    m_archives[archiveName]->defragmentArchive();
}

void LE3DatFileSystem::defragmentArchives() {
    for (auto archiveName : m_archiveNames) defragmentArchive(archiveName);
}