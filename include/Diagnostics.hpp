#pragma once
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <chrono>

/**
 * @struct Metadata
 * @brief Holds diagnostic metadata information for events.
 */
struct Metadata {
    std::string file;                          ///< Source file name.
    int line;                                  ///< Line number in the source file.
    std::string function;                      ///< Function name.
    std::vector<std::string> tags;             ///< Tags associated with the event.
    std::string correlationId;                 ///< Correlation ID for tracing events.
    std::string parentId;                      ///< Parent event ID for chaining.
    std::chrono::system_clock::time_point timestamp; ///< Timestamp of the event.
    void setTimestampMillis(int64_t millis) {
        timestamp = std::chrono::system_clock::time_point(std::chrono::milliseconds(millis));
    }

    int64_t getTimestampMillis() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            timestamp.time_since_epoch()).count();
    }
};

/**
 * @class Exporter
 * @brief Abstract base class for exporting diagnostic events.
 */
class Exporter;

/**
 * @class Diagnostics
 * @brief Provides methods for reporting and exporting diagnostic events.
 */
class Diagnostics {
public:
    /**
     * @brief Constructs a Diagnostics object.
     */
    Diagnostics();

    /**
     * @brief Adds metadata to the diagnostics context.
     * @param metadata The metadata to add.
     */
    void addMetadata(const Metadata& metadata);

    /**
     * @brief Reports a warning event.
     * @param message The warning message.
     */
    void reportWarning(const std::string& message);

    /**
     * @brief Reports an error event.
     * @param message The error message.
     */
    void reportError(const std::string& message);

    /**
     * @brief Chains this diagnostics context to a parent event.
     * @param parentId The parent event ID.
     */
    void chainTo(const std::string& parentId);

    /**
     * @brief Adds an exporter for diagnostic events.
     * @param exporter Shared pointer to an Exporter instance.
     */
    void addExporter(std::shared_ptr<Exporter> exporter);

    /**
     * @brief Sets the unique ID for this diagnostics context.
     * @param id The ID to set.
     */
    void setId(const std::string& id) { id_ = id; }

    /**
     * @brief Gets the unique ID for this diagnostics context.
     * @return The diagnostics context ID.
     */
    std::string getId() const { return id_; }

    /**
     * @brief Gets the parent event ID from the metadata.
     * @return The parent event ID.
     */
    std::string getParentId() const { return metadata_.parentId; }

private:
    Metadata metadata_;                                ///< Metadata for the current diagnostics context.
    std::vector<std::shared_ptr<Exporter>> exporters_; ///< List of exporters for diagnostic events.
    std::mutex mtx_;                                   ///< Mutex for thread safety.
    std::string id_;                                   ///< Unique ID for this diagnostics context.

    /**
     * @brief Exports a diagnostic event to all registered exporters.
     * @param level The severity level ("warning", "error", etc.).
     * @param message The event message.
     */
    void exportEvent(const std::string& level, const std::string& message);
};
