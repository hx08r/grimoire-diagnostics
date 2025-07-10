#include <grimoire/FileExporter.hpp>

FileExporter::FileExporter(const std::string& filename, bool append) {
    if (append) {
        ofs_.open(filename, std::ios::app);
    } else {
        ofs_.open(filename, std::ios::out | std::ios::trunc);
    }
}

void FileExporter::exportEvent(const std::string& serialized) {
    std::lock_guard<std::mutex> lock(mtx_);
    ofs_ << serialized << std::endl;
}
