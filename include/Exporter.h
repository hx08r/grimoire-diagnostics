#pragma once
#include <string>

class Exporter {
public:
    virtual void exportEvent(const std::string& serialized) = 0;
    virtual ~Exporter() = default;
};
