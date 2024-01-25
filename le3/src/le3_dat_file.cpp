#include "le3_dat_file.h"
using namespace le3;

#include <fmt/core.h>
using fmt::format;

#include <gzip/compress.hpp>
#include <gzip/decompress.hpp>

LE3DatFile::LE3DatFile(std::string path, std::string archiveName) : m_archiveName(archiveName) {
    createIfNotExist(path);
    m_file = std::fstream(path, std::ios::binary | std::ios::in | std::ios::out);
    if (!m_file) throw std::runtime_error(format("Could not open dat file '{}'", path));
    readDataSize();
}
LE3DatFile::~LE3DatFile() {
    if (m_file) m_file.close();
}

LE3DatBuffer LE3DatFile::loadBufferFromSystem(std::string path) {
    std::ifstream file(path, std::ios::binary);
    return LE3DatBuffer(std::istreambuf_iterator<char>(file), {});
}

void LE3DatFile::writeBufferToSystem(LE3DatBuffer buffer, std::string path) {
    std::ofstream file(path, std::ios::binary);
    std::copy(buffer.begin(), buffer.end(), std::ostreambuf_iterator<char>(file));
}

LE3DatBuffer LE3DatFile::compressBuffer(LE3DatBuffer buffer) {
    LE3DatBuffer compressedBuffer;
    std::string tmp = gzip::compress(buffer.data(), buffer.size());
    std::copy(tmp.begin(), tmp.end(), std::back_inserter(compressedBuffer));
    return compressedBuffer;
}

LE3DatBuffer LE3DatFile::decompressBuffer(LE3DatBuffer compressedBuffer) {
    LE3DatBuffer buffer;
    std::string tmp = gzip::decompress(compressedBuffer.data(), compressedBuffer.size());
    std::copy(tmp.begin(), tmp.end(), std::back_inserter(buffer));
    return buffer;
}

void LE3DatFile::createIfNotExist(std::string path) {
    std::ifstream ifile(path);
    if (ifile.good()) {
        ifile.close();
        return;
    }
    std::ofstream ofile(path);
    const char data[8] = {27}; // Write zero (4 bytes)
    ofile.write(data, 8);
    ofile.flush(); ofile.close();
}

void LE3DatFile::readDataSize() {
    m_file.seekg(-8, std::ios::end);
    char data[8]; m_file.read(data, 8);
    m_dataSize = 0; for (int i = 0; i < 8; i++)  m_dataSize = (m_dataSize << 8) | (uint8_t)data[i];
}

void LE3DatFile::readFileInfos() {

}