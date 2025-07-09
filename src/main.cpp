#include "DiagnosticAggregator.hpp"
#include "FileExporter.hpp"
#include <iostream>

int main() {
    DiagnosticAggregator manager;

    auto parentDiag = manager.createDiagnostic("parent1");
    parentDiag->setId("parent1");

    auto childDiag = manager.createDiagnostic("child1");
    childDiag->setId("child1");

    // Add exporter to parent
    auto exporter = std::make_shared<FileExporter>("diagnostics_tree.log");
    parentDiag->addExporter(exporter);
    childDiag->addExporter(exporter);

    Metadata meta;
    meta.file = __FILE__;
    meta.line = __LINE__;
    meta.function = __FUNCTION__;
    meta.tags = {"tree", "parent"};
    meta.correlationId = "root123";
    meta.timestamp = std::chrono::system_clock::now();

    parentDiag->addMetadata(meta);
    parentDiag->reportWarning("Root warning");

    Metadata childMeta = meta;
    childMeta.tags = {"tree", "child"};
    childDiag->addMetadata(childMeta);
    childDiag->reportError("Child error");

    manager.chainDiagnostics("parent1", "child1");

    manager.exportTree();

    return 0;
}
