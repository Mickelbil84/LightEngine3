#include <string>
#include <filesystem>

#include <cxxopts.hpp>
#include <fmt/core.h>

#include <core/le3_dat_archive.h>

#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES
#include <miniz.h>
#include <miniz_zip.h>

namespace fs = std::filesystem;

// Strip leading slashes from path (ZIP doesn't support them)
std::string stripLeadingSlash(const std::string& path) {
    size_t start = path.find_first_not_of('/');
    if (start == std::string::npos) return "";
    return path.substr(start);
}

// Add leading slash if not present (DAT format uses them)
std::string ensureLeadingSlash(const std::string& path) {
    if (path.empty() || path[0] == '/') return path;
    return "/" + path;
}

bool datToZip(const std::string& datPath, const std::string& zipPath) {
    if (!fs::exists(datPath)) {
        fmt::print(stderr, "Error: DAT file '{}' does not exist\n", datPath);
        return false;
    }

    le3::LE3DatArchive datArchive(datPath);
    auto fileInfos = datArchive.getFileInfos();

    if (fileInfos.empty()) {
        fmt::print(stderr, "Error: DAT archive is empty\n");
        return false;
    }

    mz_zip_archive zip;
    mz_zip_zero_struct(&zip);

    if (!mz_zip_writer_init_file(&zip, zipPath.c_str(), 0)) {
        fmt::print(stderr, "Error: Failed to create ZIP file '{}'\n", zipPath);
        return false;
    }

    fmt::print("Converting DAT to ZIP: {} -> {}\n", datPath, zipPath);

    for (const auto& [path, fileInfo] : fileInfos) {
        le3::LE3DatBuffer content = datArchive.getFileContent(path, true); // decompress

        // ZIP paths shouldn't have leading slashes
        std::string zipEntryPath = stripLeadingSlash(path);

        if (!mz_zip_writer_add_mem(&zip, zipEntryPath.c_str(),
                                    content.data.data(), content.data.size(),
                                    MZ_BEST_COMPRESSION)) {
            fmt::print(stderr, "Error: Failed to add '{}' to ZIP\n", zipEntryPath);
            mz_zip_writer_end(&zip);
            return false;
        }
        fmt::print("  Added: {}\n", zipEntryPath);
    }

    if (!mz_zip_writer_finalize_archive(&zip)) {
        fmt::print(stderr, "Error: Failed to finalize ZIP archive\n");
        mz_zip_writer_end(&zip);
        return false;
    }

    mz_zip_writer_end(&zip);
    fmt::print("Successfully converted {} files\n", fileInfos.size());
    return true;
}

bool zipToDat(const std::string& zipPath, const std::string& datPath) {
    if (!fs::exists(zipPath)) {
        fmt::print(stderr, "Error: ZIP file '{}' does not exist\n", zipPath);
        return false;
    }

    mz_zip_archive zip;
    mz_zip_zero_struct(&zip);

    if (!mz_zip_reader_init_file(&zip, zipPath.c_str(), 0)) {
        fmt::print(stderr, "Error: Failed to open ZIP file '{}'\n", zipPath);
        return false;
    }

    // Remove existing DAT file if it exists (to start fresh)
    if (fs::exists(datPath)) {
        fs::remove(datPath);
    }

    le3::LE3DatArchive datArchive(datPath);

    mz_uint numFiles = mz_zip_reader_get_num_files(&zip);
    fmt::print("Converting ZIP to DAT: {} -> {}\n", zipPath, datPath);

    mz_uint filesAdded = 0;
    for (mz_uint i = 0; i < numFiles; i++) {
        mz_zip_archive_file_stat fileStat;
        if (!mz_zip_reader_file_stat(&zip, i, &fileStat)) {
            fmt::print(stderr, "Warning: Failed to get info for file index {}\n", i);
            continue;
        }

        // Skip directories
        if (fileStat.m_is_directory) {
            continue;
        }

        // Extract file to memory
        size_t uncompSize = 0;
        void* data = mz_zip_reader_extract_to_heap(&zip, i, &uncompSize, 0);
        if (!data) {
            fmt::print(stderr, "Warning: Failed to extract '{}'\n", fileStat.m_filename);
            continue;
        }

        // Create buffer and add to DAT archive
        le3::LE3DatBuffer buffer;
        buffer.data.resize(uncompSize);
        std::memcpy(buffer.data.data(), data, uncompSize);
        mz_free(data);

        // DAT paths should have leading slashes
        std::string datEntryPath = ensureLeadingSlash(fileStat.m_filename);

        datArchive.appendFile(datEntryPath, buffer, true); // compress with gzip
        fmt::print("  Added: {}\n", datEntryPath);
        filesAdded++;
    }

    mz_zip_reader_end(&zip);
    fmt::print("Successfully converted {} files\n", filesAdded);
    return true;
}

int main(int argc, char** argv) {
    cxxopts::Options options("zipdat", "Convert between LE3 DAT archives and ZIP files");
    options.add_options()
        ("i,input", "Input file (*.dat or *.zip)", cxxopts::value<std::string>())
        ("o,output", "Output file (*.zip or *.dat)", cxxopts::value<std::string>())
        ("h,help", "Show help")
    ;
    options.parse_positional({"input", "output"});
    options.positional_help("<input> <output>");

    try {
        auto result = options.parse(argc, argv);

        if (result.count("help") || !result.count("input") || !result.count("output")) {
            fmt::print("{}\n", options.help());
            fmt::print("Examples:\n");
            fmt::print("  zipdat archive.dat archive.zip   # Convert DAT to ZIP\n");
            fmt::print("  zipdat archive.zip archive.dat   # Convert ZIP to DAT\n");
            return result.count("help") ? 0 : 1;
        }

        std::string input = result["input"].as<std::string>();
        std::string output = result["output"].as<std::string>();

        fs::path inputPath(input);
        fs::path outputPath(output);

        std::string inputExt = inputPath.extension().string();
        std::string outputExt = outputPath.extension().string();

        // Convert extensions to lowercase for comparison
        std::transform(inputExt.begin(), inputExt.end(), inputExt.begin(), ::tolower);
        std::transform(outputExt.begin(), outputExt.end(), outputExt.begin(), ::tolower);

        if (inputExt == ".dat" && outputExt == ".zip") {
            return datToZip(input, output) ? 0 : 1;
        } else if (inputExt == ".zip" && outputExt == ".dat") {
            return zipToDat(input, output) ? 0 : 1;
        } else {
            fmt::print(stderr, "Error: Invalid conversion. Input must be .dat or .zip, output must be the opposite.\n");
            fmt::print(stderr, "  Got: {} -> {}\n", inputExt, outputExt);
            return 1;
        }

    } catch (const cxxopts::exceptions::exception& e) {
        fmt::print(stderr, "Error parsing options: {}\n", e.what());
        return 1;
    }
}
