#include "Diagnostics.h"
#include "FileExporter.h"
#include <iostream>

int main() {
    Diagnostics diag;

    auto exporter = std::make_shared<FileExporter>("diagnostics.log");
    diag.addExporter(exporter);

    Metadata meta;
    meta.file = __FILE__;
    meta.line = __LINE__;
    meta.function = __FUNCTION__;
    meta.tags = {"example", "test"};
    meta.correlationId = "1234";
    meta.timestamp = std::chrono::system_clock::now();

    diag.addMetadata(meta);
    diag.reportWarning("This is a test warning.");
    diag.reportError("This is a test error.");

    std::cout << "Diagnostics reported. Check diagnostics.log" << std::endl;
    return 0;
}
