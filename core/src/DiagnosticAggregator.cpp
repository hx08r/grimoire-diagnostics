#include <grimoire/DiagnosticAggregator.hpp>
#include <grimoire/Exporter.hpp>
#include <iostream>

DiagnosticAggregator::DiagnosticAggregator() {}

std::shared_ptr<Diagnostics> DiagnosticAggregator::createDiagnostic(const std::string& id) {
    std::lock_guard<std::mutex> lock(mtx_);
    auto diag = std::make_shared<Diagnostics>();
    diagnosticsMap_[id] = diag;
    return diag;
}

void DiagnosticAggregator::chainDiagnostics(const std::string& parentId, const std::string& childId) {
    std::lock_guard<std::mutex> lock(mtx_);
    auto parentIt = diagnosticsMap_.find(parentId);
    auto childIt = diagnosticsMap_.find(childId);

    if (parentIt != diagnosticsMap_.end() && childIt != diagnosticsMap_.end()) {
        childIt->second->chainTo(parentId);
        // In future: Add real parent->children storage if needed
    } else {
        std::cerr << "Could not chain: IDs not found.\n";
    }
}

void DiagnosticAggregator::exportTree() {
    std::lock_guard<std::mutex> lock(mtx_);
    // For now: just list all diagnostics and parent IDs
    for (const auto& pair : diagnosticsMap_) {
        std::cout << "Diagnostic ID: " << pair.first << std::endl;
        // For now you’d need to add an ID field to Diagnostics to store the unique ID too
    }
}
