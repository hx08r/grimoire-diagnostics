#include "Diagnostics.hpp"
#include "FileExporter.hpp"

int main() {
    Diagnostics diag;

    Metadata meta;
    meta.file = "main.cpp";
    meta.line = 42;
    meta.function = "main";
    meta.tags = {"c++", "test"};
    meta.correlationId = "cpp123";
    meta.timestamp = std::chrono::system_clock::now();

    diag.addMetadata(meta);

    auto exporter = std::make_shared<FileExporter>("shared_diag.log", true); // append mode
    diag.addExporter(exporter);

    diag.reportWarning("C++ warning");
    diag.reportError("C++ error");

    return 0;
}
