#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace le3 {
    constexpr unsigned int MAX_PATH = 256;

    using LE3DatBuffer = std::vector<char>; // Instead of void*
    
    // Total size: 10 bytes + path length. With max length of 256 bytes, total size is 266B.
    // Hence 1000 files is ~ 0.25MB, when uncompressed.
    struct LE3FileInfo {
        uint16_t pathLen;
        std::string path;
        uint64_t offset; // Offset address in the data block. First file has offset of 0
        uint64_t packedSize; // File size inside the data block. Last address for the file is in &data[0] + offset + packedSize - 1
    }; 

    // LightEngine's take on the Fallout DAT2 file format (https://fodev.net/files/fo2/dat.html)
    // Each object is compressed with gzip, and appended to the initial data block.
    // Structre:
    //          Data block (appended gzip files)   [void*]
    //          File pool                          [void*, compressed array of LE3FileInfo]
    //          Data size                          [uint64_t]
    // File paths inside a DatFile are exactly as in a UNIX file system, e.g. "dir1/dir2" is the parent of "dir1/dir2/file1.txt"
    // TODO: allow patching
    class LE3DatFile {
    public:
        LE3DatFile(std::string path, std::string archiveName);
        ~LE3DatFile();

        // Helper methods for read-write from/to system
        LE3DatBuffer loadBufferFromSystem(std::string path);
        void writeBufferToSystem(LE3DatBuffer buffer, std::string path);

        // Helper methods for compressing and decompressing files
        LE3DatBuffer compressBuffer(LE3DatBuffer buffer);
        LE3DatBuffer decompressBuffer(LE3DatBuffer compressedBuffer);

        // TODO: append file

    protected:
        std::fstream m_file;
        std::string m_archiveName;

        std::vector<LE3FileInfo> m_fileInfos;
        uint64_t m_dataSize;

        void createIfNotExist(std::string path);

        void readDataSize();
        void readFileInfos();

        LE3DatBuffer exportFileInfos();
    };
}