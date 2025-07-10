#pragma once

#include "Diagnostics.hpp"
#include <unordered_map>
#include <memory>
#include <vector>

class CorrelationGraph {
public:
    void addNode(const std::shared_ptr<Diagnostics>& diag);
    std::shared_ptr<Diagnostics> getRootCause(const std::string& id) const;
    std::vector<std::shared_ptr<Diagnostics>> getChain(const std::string& id) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Diagnostics>> nodes_;
};
