#include <pybind11/pybind11.h>
#include <OccBox.h>

namespace py = pybind11;

void init_OccBox(py::module& m)
{
    py::class_<Occ::Box, Occ::Shape>(m, "Shape")
        .def("makeBox", &Occ::SolidMaker::makeBox, "Make a box");
}
