#include <gtest/gtest.h>
#include "Diagnostics.h"
#include "FileExporter.h"

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
