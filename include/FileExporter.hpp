#pragma once
#include "Exporter.hpp"
#include <fstream>
#include <mutex>

/**
 * @class FileExporter
 * @brief Exports serialized diagnostic events to a file.
 */
class FileExporter : public Exporter {
public:
    /**
     * @brief Constructs a FileExporter that writes to the specified file.
     * @param filename The name of the file to write events to.
     */
    FileExporter(const std::string& filename);

    /**
     * @brief Exports a serialized diagnostic event to the file.
     * @param serialized The serialized event data as a string.
     */
    void exportEvent(const std::string& serialized) override;

private:
    std::ofstream ofs_; ///< Output file stream for writing events.
    std::mutex mtx_;    ///< Mutex for thread safety during file operations.
};
