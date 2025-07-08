#pragma once
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <chrono>

struct Metadata {
    std::string file;
    int line;
    std::string function;
    std::vector<std::string> tags;
    std::string correlationId;
    std::string parentId;
    std::chrono::system_clock::time_point timestamp;
};

class Exporter;

class Diagnostics {
public:
    Diagnostics();
    void addMetadata(const Metadata& metadata);
    void reportWarning(const std::string& message);
    void reportError(const std::string& message);
    void chainTo(const std::string& parentId);
    void addExporter(std::shared_ptr<Exporter> exporter);

private:
    Metadata metadata_;
    std::vector<std::shared_ptr<Exporter>> exporters_;
    std::mutex mtx_;

    void exportEvent(const std::string& level, const std::string& message);
};
