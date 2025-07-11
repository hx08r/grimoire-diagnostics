#include <gtest/gtest.h>
#include <grimoire/FileExporter.hpp>
#include <fstream>

TEST(FileExporterTest, WritesToFile) {
    std::string filename = "test_output.log";
    {
        FileExporter exporter(filename, false);
        exporter.exportEvent("{\"test\": \"value1\"}");
        exporter.exportEvent("{\"test\": \"value2\"}");
    }

    std::ifstream infile(filename);
    ASSERT_TRUE(infile.is_open());

    std::string line1, line2;
    std::getline(infile, line1);
    std::getline(infile, line2);

    EXPECT_EQ(line1, "{\"test\": \"value1\"}");
    EXPECT_EQ(line2, "{\"test\": \"value2\"}");

    infile.close();

    std::remove(filename.c_str());
}
