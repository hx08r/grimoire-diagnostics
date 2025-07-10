#include <gtest/gtest.h>
#include <grimoire/Diagnostics.hpp>
#include <grimoire/Exporter.hpp>
#include <grimoire/FileExporter.hpp>
#include <grimoire/DiagnosticAggregator.hpp>
#include <memory>
#include <sstream>

// Mock Exporter
class MockExporter : public Exporter {
public:
    std::vector<std::string> events;

    void exportEvent(const std::string& serialized) override {
        events.push_back(serialized);
    }
};

TEST(DiagnosticsTest, MetadataIsStored) {
    Diagnostics diag;
    Metadata meta;
    meta.file = "file.cpp";
    meta.line = 42;
    meta.function = "myFunc";
    meta.tags = {"tag1", "tag2"};
    meta.correlationId = "corr123";
    meta.timestamp = std::chrono::system_clock::now();

    diag.addMetadata(meta);
    EXPECT_EQ(diag.getParentId(), "");

    diag.chainTo("parent456");
    EXPECT_EQ(diag.getParentId(), "parent456");

    diag.setId("diagID");
    EXPECT_EQ(diag.getId(), "diagID");
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

TEST(DiagnosticsTest, ExporterIsCalled) {
    auto mockExporter = std::make_shared<MockExporter>();
    Diagnostics diag;
    diag.addExporter(mockExporter);

    Metadata meta;
    meta.file = "main.cpp";
    meta.line = 10;
    meta.function = "main";
    meta.timestamp = std::chrono::system_clock::now();
    diag.addMetadata(meta);

    diag.reportWarning("This is a warning");
    diag.reportError("This is an error");

    EXPECT_EQ(mockExporter->events.size(), 2);

    EXPECT_TRUE(mockExporter->events[0].find("WARNING") != std::string::npos);
    EXPECT_TRUE(mockExporter->events[1].find("ERROR") != std::string::npos);
}

TEST(DiagnosticsTest, CorrectJSONContent) {
    auto exporter = std::make_shared<MockExporter>();
    Diagnostics diag;
    diag.addExporter(exporter);

    Metadata meta;
    meta.file = "test.cpp";
    meta.line = 123;
    meta.function = "testFunc";
    meta.tags = {"unit", "test"};
    meta.timestamp = std::chrono::system_clock::now();
    diag.addMetadata(meta);

    diag.reportError("Simulated error");

    auto lastEvent = exporter->events.back();

    EXPECT_TRUE(lastEvent.find("\"level\":\"ERROR\"") != std::string::npos);
    EXPECT_TRUE(lastEvent.find("\"file\":\"test.cpp\"") != std::string::npos);
    EXPECT_TRUE(lastEvent.find("\"message\":\"Simulated error\"") != std::string::npos);
}