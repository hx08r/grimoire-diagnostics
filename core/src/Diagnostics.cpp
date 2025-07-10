#include <grimoire/Diagnostics.hpp>
#include <grimoire/Exporter.hpp>
#include <grimoire/external/json.hpp>
#include <random>
#include <sstream>

using json = nlohmann::json;

Diagnostics::Diagnostics() {
    generateId();
}

void Diagnostics::addMetadata(const Metadata& metadata) {
    std::lock_guard<std::mutex> lock(mtx_);
    metadata_ = metadata;
}

void Diagnostics::reportWarning(const std::string& message) {
    exportEvent("WARNING", message);
}

void Diagnostics::reportError(const std::string& message) {
    exportEvent("ERROR", message);
}

void Diagnostics::chainTo(const std::string& parentId) {
    std::lock_guard<std::mutex> lock(mtx_);
    metadata_.parentId = parentId;
}

void Diagnostics::addExporter(std::shared_ptr<Exporter> exporter) {
    std::lock_guard<std::mutex> lock(mtx_);
    exporters_.push_back(exporter);
}

void Diagnostics::exportEvent(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx_);
    json j;
    j["level"] = level;
    j["message"] = message;
    j["file"] = metadata_.file;
    j["line"] = metadata_.line;
    j["function"] = metadata_.function;
    j["tags"] = metadata_.tags;
    j["correlationId"] = metadata_.correlationId;
    j["parentId"] = metadata_.parentId;
    j["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
        metadata_.timestamp.time_since_epoch()).count();

    for (auto& exporter : exporters_) {
        exporter->exportEvent(j.dump());
    }
}

void Diagnostics::generateId() {
    id_ = generateUUID();
}

std::string Diagnostics::generateUUID() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    ss << std::hex;
    for (int i = 0; i < 8; ++i) ss << dis(gen);
    ss << "-";
    for (int i = 0; i < 4; ++i) ss << dis(gen);
    ss << "-4"; // UUID v4
    for (int i = 0; i < 3; ++i) ss << dis(gen);
    ss << "-";
    ss << dis(gen) % 4 + 8; // variant
    for (int i = 0; i < 3; ++i) ss << dis(gen);
    ss << "-";
    for (int i = 0; i < 12; ++i) ss << dis(gen);
    return ss.str();
}
