#pragma once
#include "Exporter.h"
#include <fstream>
#include <mutex>

class FileExporter : public Exporter {
public:
    FileExporter(const std::string& filename);
    void exportEvent(const std::string& serialized) override;

private:
    std::ofstream ofs_;
    std::mutex mtx_;
};
