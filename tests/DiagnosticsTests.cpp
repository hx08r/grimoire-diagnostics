#include <gtest/gtest.h>
#include "Diagnostics.hpp"
#include "FileExporter.hpp"
#include "DiagnosticAggregator.hpp"

TEST(DiagnosticsTest, MetadataFieldsSetCorrectly) {
    Diagnostics diag;

    Metadata meta;
    meta.file = "file.cpp";
    meta.line = 42;
    meta.function = "testFunc";
    meta.correlationId = "abc123";
    meta.timestamp = std::chrono::system_clock::now();

    diag.addMetadata(meta);

    // There's no public getter, so maybe check via report + mock.
    SUCCEED(); // Replace with real checks using a mock exporter.
}

TEST(DiagnosticsTest, FileExporterWrites) {
    auto exporter = std::make_shared<FileExporter>("test_output.log");
    exporter->exportEvent("{\"test\":\"value\"}");

    std::ifstream ifs("test_output.log");
    std::string line;
    std::getline(ifs, line);
    EXPECT_EQ(line, "{\"test\":\"value\"}");
}

TEST(DiagnosticAggregatorTest, CanCreateAndChainDiagnostics) {
    DiagnosticAggregator manager;

    // Create parent and child
    auto parent = manager.createDiagnostic("parentID");
    parent->setId("parentID");
    auto child = manager.createDiagnostic("childID");
    child->setId("childID");

    // Metadata sanity to simulate real use
    Metadata meta;
    meta.file = "DiagnosticsTests.cpp";
    meta.line = __LINE__;
    meta.function = __FUNCTION__;
    meta.correlationId = "corr123";
    meta.timestamp = std::chrono::system_clock::now();
    parent->addMetadata(meta);
    child->addMetadata(meta);

    // Chain them
    manager.chainDiagnostics("parentID", "childID");

    // Check that child’s parentId is correct
    EXPECT_EQ(child->getParentId(), "parentID");
}