#pragma once
#include <string>

/**
 * @class Exporter
 * @brief Abstract base class for exporting serialized diagnostic events.
 */
class Exporter {
public:
    /**
     * @brief Exports a serialized diagnostic event.
     * @param serialized The serialized event data as a string.
     */
    virtual void exportEvent(const std::string& serialized) = 0;

    /**
     * @brief Virtual destructor for safe cleanup of derived classes.
     */
    virtual ~Exporter() = default;
};
