#include "FileExporter.hpp"

FileExporter::FileExporter(const std::string& filename) {
    ofs_.open(filename, std::ios::app);
}

void FileExporter::exportEvent(const std::string& serialized) {
    std::lock_guard<std::mutex> lock(mtx_);
    ofs_ << serialized << std::endl;
}
