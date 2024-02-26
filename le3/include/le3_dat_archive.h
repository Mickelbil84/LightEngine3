#pragma once

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>

// LightEngine's take on the Fallout DAT2 file format (https://fodev.net/files/fo2/dat.html)
// Each object is compressed with gzip, and appended to the initial data block.
// Structre:
//          Data block (appended gzip files)   [void*]
//          File pool                          [void*, compressed array of LE3FileInfo]
//          Data size                          [uint64_t]
// File paths inside a DatFile are exactly as in a UNIX file system, e.g. "dir1/dir2" is the parent of "dir1/dir2/file1.txt"
// TODO: allow patching
namespace le3 {

    // Total size: 10 bytes + path length. With max length of 256 bytes, total size is 266B.
    // Hence 1000 files is ~ 0.25MB, when uncompressed.
    struct LE3FileInfo {
        uint16_t pathLen;
        std::string path;
        uint64_t offset; // Offset address in the data block. First file has offset of 0
        uint64_t packedSize; // File size inside the data block. Last address for the file is in &data[0] + offset + packedSize - 1

        std::string str();
    }; 

    struct LE3DatBuffer {
    public:
        std::vector<char> data;
        bool bCompressed = false;

        // Read write methods
        template<class T> inline void writeBuffer(T out) { std::copy(data.begin(), data.end(), out); }
        template<class T> inline void readBuffer(T first, T last) { std::copy(first, last, std::back_inserter(data)); }
        inline void appendBuffer(LE3DatBuffer other) { readBuffer(other.data.begin(), other.data.end()); }
        inline void fromString(std::string strData) { data.clear(); readBuffer(strData.begin(), strData.end()); }
        inline std::string toString() { std::string res; writeBuffer(std::back_inserter(res)); return res; }
        static LE3DatBuffer loadFromSystem(std::string path, bool compressed = false);

        // Pushing and popping integers (larger than 1 byte)
        template<typename T> inline void pushInteger(T num);
        template<typename T> inline T readInteger();

        // Useful for reading file info structure
        template<typename T> inline T readIntegerFrom(uint64_t start);
        inline std::string readStringFrom(uint64_t start, uint16_t count);

        // Compression
        void compress(); 
        void decompress();
    };

    class LE3DatArchive {
    public:
        LE3DatArchive(std::string archivePath);
        LE3DatArchive(LE3DatArchive& other);
        ~LE3DatArchive();

        inline std::map<std::string, LE3FileInfo> getFileInfos() const { return m_fileInfos; }
        inline uint64_t getDataSize() const { return m_dataSize; }

        // You can modify an existing path by appending into the same path. This will create fragmentation!
        void appendFile(std::string path, LE3DatBuffer fileBuffer, bool shouldCompress = true);
        void defragmentArchive();

        LE3DatBuffer getFileContent(std::string path, bool shouldDecompress = true);
        
    private:
        std::fstream m_archiveFile;
        std::string m_archivePath;

        std::map<std::string, LE3FileInfo> m_fileInfos;
        uint64_t m_dataSize = 0;

        // An archive with this name might get deleted! Beware
        static constexpr char TMP_ARCHIVE[] = "__tmp.dat"; 

        // Helper methods
        void createArchiveIfNotExist();
        void loadArchive();
        void openArchive();
        void closeArchive();
        void flushArchive();

        void readDataSize();
        void readFileInfos();
        LE3DatBuffer readFileInfosSegment(); // Read the entire chunk into memory

        void truncateFileInfos(); // Only from dat file, so that it can be rewritten
        LE3DatBuffer serializeFileInfo(LE3FileInfo fileInfo);
        void writeFileContent(LE3DatBuffer buffer);
        void writeFileInfos();
        void writeDataSize();
    };
    using LE3DatArchivePtr = std::unique_ptr<LE3DatArchive>;
}