#include <pybind11/pybind11.h>
#include <OccSolidMaker.h>

namespace py = pybind11;

void init_OccSolidMaker(py::module& m)
{
    py::class_<Occ::SolidMaker>(m, "SolidMaker")
        .def("makeBox", &Occ::SolidMaker::makeBox, "Make a box")
        .def("makeCylinder", &Occ::SolidMaker::makeCylinder, "Make a cylinder");
}
