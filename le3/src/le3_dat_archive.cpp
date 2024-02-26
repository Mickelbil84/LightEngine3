#include "le3_dat_archive.h"
using namespace le3;

#include <stdexcept>

#include <fmt/core.h>

#include <gzip/compress.hpp>
#include <gzip/decompress.hpp>

std::string LE3FileInfo::str() {
    return fmt::format("({}) '{}' @ {} [{}]", pathLen, path, offset, packedSize);
}

LE3DatBuffer LE3DatBuffer::loadFromSystem(std::string path, bool compressed) {
    std::ifstream ifile(path, std::ios::binary);
    if (!ifile.good()) throw std::runtime_error(fmt::format("Could not load file '{}'", path));
    LE3DatBuffer buffer; buffer.bCompressed = compressed;
    buffer.readBuffer(std::istreambuf_iterator<char>(ifile), std::istreambuf_iterator<char>());
    ifile.close();
    return buffer;
}

template<typename T> 
void LE3DatBuffer::pushInteger(T num) {
    for (int i = 0; i < sizeof(T); i++) {
        data.push_back((int8_t) (num >> ((sizeof(T) - 1 - i) * 8)) & 0x0FF);
    }
}
template<typename T> 
T LE3DatBuffer::readInteger() {
    // T num = 0x0;
    // for (int i = sizeof(T); i > 0; i--) num = (num << 0x08) | data[data.size() - i];
    // return num;
    return readIntegerFrom<T>(data.size() - sizeof(T));
}

template<typename T> 
T LE3DatBuffer::readIntegerFrom(uint64_t start) {
    T num = 0x0;
    for (int i = start; i < start + sizeof(T); i++) {
        num = (num << 0x08) | (uint8_t)data[i];
    }
    return num;
}
std::string LE3DatBuffer::readStringFrom(uint64_t start, uint16_t count) {
    std::string res;
    std::copy(&data[start], &data[start + count], std::back_inserter(res));
    return res;
}

void LE3DatBuffer::compress() {
    // if (bCompressed) return;
    fromString(gzip::compress(data.data(), data.size()));
    bCompressed = true;
}
void LE3DatBuffer::decompress() {
    // if (!bCompressed) return;
    fromString(gzip::decompress(data.data(), data.size()));
    bCompressed = false;
}

LE3DatArchive::LE3DatArchive(std::string archivePath) : m_archivePath(archivePath) {
    createArchiveIfNotExist();
    loadArchive();
}
LE3DatArchive::LE3DatArchive(LE3DatArchive& other) : m_archivePath(other.m_archivePath) {
    createArchiveIfNotExist();
    loadArchive();
}
LE3DatArchive::~LE3DatArchive() {
    closeArchive();
}

void LE3DatArchive::createArchiveIfNotExist() {
    std::ifstream ifile(m_archivePath);
    if (ifile.good()) {
        ifile.close();
        return;
    }
    std::ofstream ofile(m_archivePath);
    LE3DatBuffer buffer; buffer.pushInteger((uint64_t)0);
    buffer.writeBuffer(std::ostreambuf_iterator(ofile));
    ofile.flush(); ofile.close();
}
void LE3DatArchive::loadArchive() {
    openArchive();
    readDataSize();
    readFileInfos();
}
void LE3DatArchive::openArchive() {
    m_archiveFile = std::fstream(m_archivePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!m_archiveFile) throw std::runtime_error(fmt::format("Could not open *.dat file '{}'", m_archivePath));
}
void LE3DatArchive::closeArchive() {
    if (m_archiveFile) m_archiveFile.close();
}
void LE3DatArchive::flushArchive() {
    m_archiveFile.flush();
}

void LE3DatArchive::readDataSize() {
    char tmp[sizeof(uint64_t)];
    m_archiveFile.seekg(-sizeof(uint64_t), std::ios::end);
    m_archiveFile.read(tmp, sizeof(uint64_t));
    LE3DatBuffer buffer;
    buffer.readBuffer(&tmp[0], &tmp[sizeof(uint64_t)]);
    m_dataSize = buffer.readInteger<uint64_t>();
}
void LE3DatArchive::readFileInfos() {
    m_fileInfos.clear();

    LE3DatBuffer fileInfoSegment = readFileInfosSegment();
    uint64_t cursor = 0;
    while (cursor < fileInfoSegment.data.size()) {
        LE3FileInfo fileInfo;
        fileInfo.pathLen = fileInfoSegment.readIntegerFrom<uint16_t>(cursor); cursor += sizeof(uint16_t);
        fileInfo.path = fileInfoSegment.readStringFrom(cursor, fileInfo.pathLen); cursor += fileInfo.pathLen;
        fileInfo.offset = fileInfoSegment.readIntegerFrom<uint64_t>(cursor); cursor += sizeof(uint64_t);
        fileInfo.packedSize = fileInfoSegment.readIntegerFrom<uint64_t>(cursor); cursor += sizeof(uint64_t);
        m_fileInfos[fileInfo.path] = fileInfo;
    }
    
}

LE3DatBuffer LE3DatArchive::readFileInfosSegment() {
    // Get start and end locations
    m_archiveFile.seekg(m_dataSize, std::ios::beg);
    auto startPos = m_archiveFile.tellg();
    m_archiveFile.seekg(-sizeof(uint64_t), std::ios::end);
    auto endPos = m_archiveFile.tellg();

    // Go back to start, and read the according amount of chars
    char* tmp = new char[endPos - startPos];
    m_archiveFile.seekg(m_dataSize, std::ios::beg);
    m_archiveFile.read(tmp, endPos - startPos);
    LE3DatBuffer buffer; buffer.readBuffer(&tmp[0], &tmp[endPos - startPos]);
    delete[] tmp;

    return buffer;
}

void LE3DatArchive::appendFile(std::string path, LE3DatBuffer fileBuffer, bool shouldCompress) {
    if (shouldCompress) fileBuffer.compress();

    // Create file metadata
    LE3FileInfo fileInfo;
    fileInfo.path = path;
    fileInfo.pathLen = path.size();
    fileInfo.offset = m_dataSize;
    fileInfo.packedSize = fileBuffer.data.size();
    m_fileInfos[fileInfo.path] = fileInfo;

    truncateFileInfos();
    writeFileContent(fileBuffer);
    writeFileInfos();

    m_dataSize += fileInfo.packedSize;
    writeDataSize();
}

void LE3DatArchive::truncateFileInfos() {
    closeArchive();
    std::filesystem::resize_file(m_archivePath, m_dataSize);
    openArchive();
}

LE3DatBuffer LE3DatArchive::serializeFileInfo(LE3FileInfo fileInfo) {
    LE3DatBuffer buffer;
    buffer.pushInteger(fileInfo.pathLen);
    buffer.readBuffer(fileInfo.path.begin(), fileInfo.path.end());
    buffer.pushInteger(fileInfo.offset);
    buffer.pushInteger(fileInfo.packedSize);
    return buffer;
}

void LE3DatArchive::writeFileContent(LE3DatBuffer buffer) {
    m_archiveFile.seekg(0, std::ios::end);
    buffer.writeBuffer(std::ostreambuf_iterator(m_archiveFile));
    flushArchive();
}

void LE3DatArchive::writeFileInfos() {
    LE3DatBuffer fileInfosSegment;
    for (auto kv : m_fileInfos) fileInfosSegment.appendBuffer(serializeFileInfo(kv.second));
    m_archiveFile.seekg(0, std::ios::end);
    fileInfosSegment.writeBuffer(std::ostreambuf_iterator(m_archiveFile));
    flushArchive();
}

void LE3DatArchive::writeDataSize() {
    LE3DatBuffer buffer; buffer.pushInteger((uint64_t)m_dataSize);
    buffer.writeBuffer(std::ostreambuf_iterator(m_archiveFile));
    flushArchive();
}

LE3DatBuffer LE3DatArchive::getFileContent(std::string path, bool shouldDecompress) {
    if (!m_fileInfos.contains(path)) throw std::runtime_error(fmt::format("Path '{}' does not exist in archive", path));
    LE3FileInfo fileInfo = m_fileInfos[path];

    char* tmp = new char[fileInfo.packedSize];
    m_archiveFile.seekg(fileInfo.offset, std::ios::beg);
    m_archiveFile.read(tmp, fileInfo.packedSize);

    LE3DatBuffer buffer;
    buffer.readBuffer(&tmp[0], &tmp[fileInfo.packedSize]);
    if (shouldDecompress) buffer.decompress();
    delete[] tmp;
    return buffer;
}

void LE3DatArchive::defragmentArchive() {
    std::filesystem::remove(LE3DatArchive::TMP_ARCHIVE);
    LE3DatArchive tmpArchive(LE3DatArchive::TMP_ARCHIVE);
    for (auto kv : m_fileInfos) {
        tmpArchive.appendFile(kv.second.path, getFileContent(kv.second.path, false), false);
    }
    tmpArchive.closeArchive();
    this->closeArchive();
    std::filesystem::remove(m_archivePath);
    std::filesystem::rename(LE3DatArchive::TMP_ARCHIVE, m_archivePath);
    loadArchive();
}