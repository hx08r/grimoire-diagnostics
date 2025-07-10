#pragma once

#include "Diagnostics.hpp"
#include <unordered_map>
#include <memory>
#include <string>
#include <mutex>

/**
 * @class DiagnosticAggregator
 * @brief Manages multiple Diagnostics instances and their relationships.
 */
class DiagnosticAggregator {
public:
    /**
     * @brief Constructs a DiagnosticAggregator object.
     */
    DiagnosticAggregator();

    /**
     * @brief Creates a new Diagnostics instance with a unique ID.
     * @param id The unique identifier for the Diagnostics instance.
     * @return Shared pointer to the created Diagnostics instance.
     */
    std::shared_ptr<Diagnostics> createDiagnostic(const std::string& id);

    /**
     * @brief Chains a child Diagnostics context to a parent context.
     * @param parentId The ID of the parent Diagnostics context.
     * @param childId The ID of the child Diagnostics context.
     */
    void chainDiagnostics(const std::string& parentId, const std::string& childId);

    /**
     * @brief Exports the full diagnostics tree.
     * @note This is a placeholder function.
     */
    void exportTree();

private:
    std::unordered_map<std::string, std::shared_ptr<Diagnostics>> diagnosticsMap_; ///< Map of Diagnostics instances by ID.
    std::mutex mtx_; ///< Mutex for thread safety.
};
