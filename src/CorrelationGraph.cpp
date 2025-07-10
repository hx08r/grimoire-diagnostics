#include "CorrelationGraph.hpp"
#include <stdexcept>

void CorrelationGraph::addNode(const std::shared_ptr<Diagnostics>& diag) {
    nodes_[diag->getId()] = diag;
}

std::shared_ptr<Diagnostics> CorrelationGraph::getRootCause(const std::string& id) const {
    auto it = nodes_.find(id);
    if (it == nodes_.end()) throw std::runtime_error("ID not found");
    auto current = it->second;

    while (!current->getParentId().empty()) {
        auto parentIt = nodes_.find(current->getParentId());
        if (parentIt == nodes_.end()) break;
        current = parentIt->second;
    }
    return current;
}

std::vector<std::shared_ptr<Diagnostics>> CorrelationGraph::getChain(const std::string& id) const {
    std::vector<std::shared_ptr<Diagnostics>> chain;
    auto it = nodes_.find(id);
    if (it == nodes_.end()) return chain;

    auto current = it->second;
    while (current) {
        chain.push_back(current);
        if (current->getParentId().empty()) break;

        auto parentIt = nodes_.find(current->getParentId());
        if (parentIt == nodes_.end()) break;

        current = parentIt->second;
    }
    return chain;
}
