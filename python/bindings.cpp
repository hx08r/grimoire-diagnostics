// bindings.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../include/Diagnostics.hpp"
#include "../include/FileExporter.hpp"

namespace py = pybind11;

PYBIND11_MODULE(grimoire_diag, m) {
    py::class_<Metadata>(m, "Metadata")
        .def(py::init<>())
        .def_readwrite("file", &Metadata::file)
        .def_readwrite("line", &Metadata::line)
        .def_readwrite("function", &Metadata::function)
        .def_readwrite("tags", &Metadata::tags)
        .def_readwrite("correlationId", &Metadata::correlationId)
        .def_readwrite("parentId", &Metadata::parentId)
        .def("set_timestamp", &Metadata::setTimestampMillis)
        .def("get_timestamp", &Metadata::getTimestampMillis);

    py::class_<Diagnostics, std::shared_ptr<Diagnostics>>(m, "Diagnostics")
        .def(py::init<>())
        .def("add_metadata", &Diagnostics::addMetadata)
        .def("report_warning", &Diagnostics::reportWarning)
        .def("report_error", &Diagnostics::reportError)
        .def("chain_to", &Diagnostics::chainTo)
        .def("add_exporter", &Diagnostics::addExporter)
        .def("set_id", &Diagnostics::setId)
        .def("get_id", &Diagnostics::getId)
        .def("get_parent_id", &Diagnostics::getParentId);

    py::class_<Exporter, std::shared_ptr<Exporter>>(m, "Exporter");

    py::class_<FileExporter, Exporter, std::shared_ptr<FileExporter>>(m, "FileExporter")
        .def(py::init<const std::string&, bool>(), py::arg("filename"), py::arg("append") = true);
}
